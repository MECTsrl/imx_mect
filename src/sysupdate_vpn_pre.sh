#!/bin/sh

# Trace the execution.
set -x

ERRMSG="SYSUPDATE ERROR:"

# Set in /etc/rc.d/init.d/S10setup
MNTDIR=/tmp/mnt

SHADOWFILE="/etc/shadow"
RFSVFILE="/rootfs_version"
SNFILE="/etc/serial.conf"
CRONTAB="/local/var/spool/cron/crontabs/root"
OVPNCONF="/etc/openvpn"
OVPNRC="/etc/rc.d/init.d/openvpn"
CRONRC="/etc/rc.d/init.d/crond"

# Non-empty argument means to print that as error message and to exit with an error code.
do_exit()
{
    sync 2>&1 | tee /dev/tty1

    # Restore the root file system access mode.
    test "$RFSRW" -ne 0 && mount -oro,remount /

    test -n "$1" && echo -e "${ERRMSG} $1\r" | tee /dev/tty1
    echo -e "\r" | tee /dev/tty1
    echo -e "*******************************************************\r" | tee /dev/tty1
    echo -e "* Please power off and remove the USB storage device. *\r" | tee /dev/tty1
    echo -e "*******************************************************\r" | tee /dev/tty1

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

    # Still mounted R/O?  Error out!
    grep -q '\s/\s\+ubifs\s\+.*\brw\b' /proc/mounts || do_exit "read-only root file system."
fi

test -s "$SHADOWFILE" -a -r "$SHADOWFILE" || do_exit "missing the password file."
test -s "$RFSVFILE" -a -r "$RFSVFILE" || do_exit "malformed root file system."
test -s "$SNFILE" -a -r "$SNFILE" || do_exit "serial number not set."

# Collect info about the installed system.
#

# Image version
RELEASE="$(awk '/^Release/ { print $2; }' "$RFSVFILE")"
test -z "$RELEASE" && do_exit "missing installed SW version."

# Target system type
TARGET="$(awk '/^Target/ { print $2; }' "$RFSVFILE")"
test -z "$TARGET" && do_exit "cannot find the device type."

# Device serial number
SN="$(cat "$SNFILE")"
test -z "$SN" && do_exit "cannot find device serial number."
echo "Board Serial Number: ${SN}"  | tee /dev/tty1

# OpenVPN RC script
test -s "$OVPNRC" || do_exit "missing OpenVPN control script (RC)."

echo -e "Updating $TARGET SW v$RELEASE for MECT Remote Services.\r" | tee /dev/tty1

# Update the device.
#

cd /

