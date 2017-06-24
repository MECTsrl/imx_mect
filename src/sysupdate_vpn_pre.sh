#!/bin/sh

# Trace the execution.
set -x

ERRMSG="SYSUPDATE ERROR:"

# Set in /etc/rc.d/init.d/S10setup
MNTDIR=/tmp/mnt

LUS="/usr/sbin/rsync-mect.sh"
LUP="/etc/rsync-mect.pwd"
CRONTAB="/local/var/spool/cron/crontabs/root"
OVPNCONF="/etc/openvpn"
OVPNRC="/etc/rc.d/init.d/openvpn"
CRONRC="/etc/rc.d/init.d/crond"

# Non-empty argument means to print that as error message and to exit with an error code.
do_exit()
{
    sync 2>&1 | tee /dev/tty1

    test -n "$1" && echo "${ERRMSG} $1" | tee /dev/tty1
    echo "" | tee /dev/tty1
    echo "*******************************************************" | tee /dev/tty1
    echo "* Please power off and remove the USB storage device. *" | tee /dev/tty1
    echo "*******************************************************" | tee /dev/tty1

    while true; do read -rp "" dummy; done

    # Never reached
    if test -n "$1"; then
        exit 1
    else
        exit 0
    fi
}

# Gain R/W access to root file system.
RFSRW="$(grep -q '\s/\s\+ubifs\s.*\brw\b' /proc/mounts; echo $?)"
if test "$RFSRW" -ne 0; then
    mount -orw,remount /
    grep -q '\s/\s\+ubifs\s\+.*\brw\b' /proc/mounts || do_exit "read-only root file system."
fi

test -s /rootfs_version -a -r /rootfs_version   || do_exit "malformed root file system."
test -s /etc/serial.conf -a -r /etc/serial.conf || do_exit "serial number not set."

# Collect info about the installed system.
#

# Image version
RELEASE="$(awk '/^Release/ { print $2; }' /rootfs_version)"
test -z "$RELEASE" && do_exit "missing installed SW version."

# Target system type
TARGET="$(awk '/^Target/ { print $2; }' /rootfs_version)"
test -z "$TARGET" && do_exit "cannot find the device type."

# Device serial number
SN="$(cat /etc/serial.conf)"
test -z "$SN" && do_exit "cannot find device serial number."

# OpenVPN RC script
test -s "$OVPNRC" || do_exit "missing OpenVPN control script (RC)."

echo "Updating $TARGET SW v$RELEASE for MECT Remote Services." | tee /dev/tty1

# Update the device.
#

cd /

