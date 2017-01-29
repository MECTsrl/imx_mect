#!/bin/sh

set -e
#set -x

function cleanup
{
    test -d "$unpackdir" && rm -rf "$unpackdir"
}
trap cleanup EXIT

function checkdep
{
    while test -n "$1"; do
        type -p "$1" > /dev/null || { echo "Missing dependency $1." >&2; exit 1; }

        shift
    done
}

checkdep realpath dirname basename mktemp unzip find tar sshpass scp ssh rm mkdir rsync

user="root"
passwd="root"

k_arch_name="imx28_ivt_linux.sb"
kupd_name="kobs-ng"
kupd="$(realpath -P $(dirname $(realpath -P $0))/../../src/$kupd_name)"
rfs_arch_name="rootfs.tar"
lfs_arch_name="localfs.tar"

prog="$(basename $0)"
test -z "$prog" && { echo "$0: cannot determine program name." >&2; exit 1; }

function usage
{
    echo "Usage: $prog <image archive> <target IP address>" >&2
}


arch="$1"
test -z "$arch" && { usage; exit 1; }
arch="$(realpath -L $arch)"
test -r "$arch" || { echo "$prog: cannot read image archive $arch." >&2; exit 1; }
unzip -t "$arch" || { echo "$prog: archive $arch integrity test failed." >&2; exit 1; }

ip="$2"
test -z "$ip" && { usage; exit 1; }

test -z "$user" && { echo "$prog: no target user name." >&2; exit 1; }
test -z "$k_arch_name" && { echo "$prog: no kernel archive name." >&2; exit 1; }
test -z "$kupd" && { echo "$prog: no kernel updater name." >&2; exit 1; }
test -z "$rfs_arch_name" && { echo "$prog: no root file system archive name." >&2; exit 1; }
test -z "$lfs_arch_name" && { echo "$prog: no local file system archive name." >&2; exit 1; }

kupd="$(realpath -L $kupd)"
test -x "$kupd" || { echo "$prog: cannot kernel updater program $kupd_name." >&2; exit 1; }

unpackdir="$(mktemp -p $(pwd) -d $(basename $0).XXXXXXXXXX)"
test -d "$unpackdir" || { echo "$prog: cannot create working directory $unpackdir." >&2; exit 1; }

cd "$unpackdir"
unzip "$arch"

k_arch="$(find . -type f -name $k_arch_name -print)"
test -z "$k_arch" && { echo "$prog: kernel archive $k_arch_name not found." >&2; exit 1; }
test -r "$k_arch" || { echo "$prog: cannot read kernel archive $k_arch." >&2; exit 1; }

test -r "$kupd" || { echo "$prog: cannot read kernel updater $kupd." >&2; exit 1; }

rfs_arch="$(find . -type f -name $rfs_arch_name -print)"
test -z "$rfs_arch" && { echo "$prog: root file system archive $rfs_arch_name not found." >&2; exit 1; }
test -r "$rfs_arch" || { echo "$prog: cannot read root file system archive $rfs_arch." >&2; exit 1; }
tar tf "$rfs_arch" > /dev/null || { echo "$prog: cannot unpack root file system archive $rfs_arch." >&2; exit 1; }

lfs_arch="$(find . -type f -name $lfs_arch_name -print)"
test -z "$lfs_arch" && { echo "$prog: local file system archive $lfs_arch_name not found." >&2; exit 1; }
test -r "$lfs_arch" || { echo "$prog: cannot read local file system archive $lfs_arch." >&2; exit 1; }
tar tf "$lfs_arch" > /dev/null || { echo "$prog: cannot unpack local file system archive $lfs_arch." >&2; exit 1; }

set +e

sshpass -p "$passwd" scp "$kupd" "$k_arch" "$user"@"$ip":/tmp
sshpass -p "$passwd" ssh root@"$ip" \
    flash_eraseall /dev/mtd0\; \
    /tmp/$kupd_name init /tmp/$k_arch_name\; \
    rm -f /tmp/$kupd_name /tmp/$k_arch_name\; \
    mount -orw,remount /

rm -rf rootfs
mkdir -p rootfs
test -d rootfs
tar xf "$rfs_arch" -C rootfs
sshpass -p "$passwd" rsync -axh --inplace --delete --info=progress2 rootfs/ "$user"@"$ip":/
sshpass -p "$passwd" rsync -axh --delete --info=progress2 rootfs/ "$user"@"$ip":/

rm -rf localfs
mkdir -p localfs
test -d localfs
tar xf "$lfs_arch" -C localfs
sshpass -p "$passwd" rsync -axh --inplace --info=progress2 localfs/local/ "$user"@"$ip":/local/
sshpass -p "$passwd" rsync -axh --info=progress2 localfs/local/ "$user"@"$ip":/local/
