#!/bin/sh

# Trace the execution.
set -x

ERRMSG="SYSUPDATE ERROR:"

# Set in /etc/rc.d/init.d/S10setup
TMP_RAM_DIR=/tmp/ram
NEWNETFILE="$TMP_RAM_DIR/net.conf"


NETFILE="/local/flash/etc/sysconfig/net.conf"
RFSVFILE="/rootfs_version"
SNFILE="/etc/serial.conf"

# Non-empty argument means to print that as error message and to exit with an error code.
do_exit()
{
    sync 2>&1 | tee /dev/tty1


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


test -s "$NETFILE" -a -r "$NETFILE" || do_exit "missing the network config file."
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

#killing hmi & application and watchdog
/etc/rc.d/init.d/autoexec stop
/sbin/devmem 0x80056008 32 0x00000010

#Set up ram directory
if [ -d ${TMP_RAM_DIR} ]
then 
	echo "${TMP_RAM_DIR} already exist..." | tee /dev/tty1
else
	mkdir -p ${TMP_RAM_DIR}
fi

# Extract update file
echo "Extract update files" | tee /dev/tty1
if uudecode $0 
then
	echo "Decoded update file!" | tee /dev/tty1
else
	do_exit "error decoding update file"
fi

# Reset Ip address
test -e $NEWNETFILE || do_exit "New Net config file not found ${NEWNETFILE}."
cp "$NEWNETFILE" "$NETFILE"

# All set.
( echo -e "\r"; echo -e "Network configuration resetted to default .\r" ) | tee /dev/tty1
do_exit


