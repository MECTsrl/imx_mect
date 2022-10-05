#!/bin/sh

#sysupdate_factory: Same as sysupdate_imx28_img but only restore Simple application like does Cloner

# Execution trace
# set -x

SYSTMPDIR="/tmp"
MYTMPDIR="${SYSTMPDIR}/$(basename $0).$$"
MNTDIR="/tmp/mnt"               # Set in /etc/rc.d/init.d/S10setup
IMGDIR="/tmp/sysupdate"
SUDIR="sysupdate"               # sysupdate-specific dir within the image
PASSWDDIR="/etc"
PASSWD="shadow"

trap cleanup EXIT
cleanup()
{
        cd /

        sleep 2                 # Wait for programs to terminate.

        losetup | grep -q . && umount $(losetup | awk -F: '{ print $1}')
        losetup | grep -q . && losetup -d $(losetup | awk -F: '{ print $1}')

        rm -rf "$MYTMPDIR"

        sync
}

# Non-empty argument means print it as error message and exit with error code.
do_exit()
{
	sync 2>&1 | tee /dev/tty1

	test -n "$1" && echo "SYSUPDATE ERROR: $1" | tee /dev/tty1
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

if ! test -r /rootfs_version; then
	do_exit "malformed root file system."
fi

# Stop most of the running processes and watchdog.
/etc/rc.d/init.d/autoexec stop
/etc/rc.d/init.d/crond stop
/etc/rc.d/init.d/boa stop
/etc/rc.d/init.d/inetd stop
/sbin/devmem 0x80056008 32 0x00000010

# Collect info on installed system
#

# Image version
RELEASE="`awk '/^Release/ { print $2; }' /rootfs_version`"
test -n "$RELEASE" || do_exit "cannot find the installed version."

# Target system type
TARGET="`awk '/^Target/ { print $2; }' /rootfs_version`"
test -n "$TARGET" || do_exit "cannot find the system type."

# Check the compatibility of the update with the installed version (Only whitin current Version).
if [ $RELEASE != '@@THIS_VERSION@@' ]; then
   do_exit "cannot update the installed version ${RELEASE} with @@THIS_VERSION@@."
fi
#expr "$RELEASE" : @@THIS_VERSION_MAJ_MIN@@ > /dev/null || expr "$RELEASE" : 3\\.3 > /dev/null || expr "$RELEASE" : 3\\.2 > /dev/null || expr "$RELEASE" : 3\\.1 > /dev/null || do_exit "cannot update the installed version ${RELEASE}."

# Check if we have an update for the running target.
UPDIMG="${MNTDIR}/img_sysupdate-@@THIS_VERSION@@-${TARGET}.ext2"
test -r "$UPDIMG" || do_exit "cannot find an update for ${TARGET}."

# Set up the temporary directory.
mkdir -p "$MYTMPDIR"
test -d "$MYTMPDIR" || do_exit "cannot create temporary directory ${MYTMPDIR}."
chmod 700 "$MYTMPDIR"

# Clean idle setups.
losetup | grep -q . && losetup -d $(losetup | awk -F: '{ print $1}')

# Prepare sysupdate image mount point.
test -d "$IMGDIR" && rm -rf "$IMGDIR"
mkdir -p "$IMGDIR"
test -d "$IMGDIR" || do_exit "cannot create image directory ${IMGDIR}."

# Mount the sysupdate image.
mount -o ro,loop "$UPDIMG" "$IMGDIR" || do_exit "cannot mount cloner image ${CLONEIMG}."

# Start the update.
#Remove all hmi files
rm -f /local/hmi*

# Update the local file system.
# FIX: Come gestire gli Exclude di Cloner --exclude hmi*
echo "Restoring  @@THIS_VERSION@@ Simple Application on the $TARGET." | tee /dev/tty1
echo "" | tee /dev/tty1
if test -d ${IMGDIR}/local; then
	echo "Updating the local file system..." | tee /dev/tty1
	rsync -aHc  ${IMGDIR}/local/ /local/  --exclude flash/root/fcrts --exclude flash/etc/sysconfig/net.conf --exclude flash/etc/wpa_supplicant/default.conf --exclude flash/etc/ppp --exclude var/spool/cron/crontabs/root --exclude sd_card  2>&1 | tee /dev/tty1
	echo "done." | tee /dev/tty1
fi
# Cleaning up /local/data
echo "Clean Storage files" | tee /dev/tty1
rm -rf /local/data 2>&1 | tee /dev/tty1
mkdir -p /local/data 2>&1 | tee /dev/tty1

#Clean Retentive
echo "Clean Retentive" | tee /dev/tty1
dd if=/dev/zero of=/local/retentive bs=768 count=1 2>&1 | tee /dev/tty1

# Cleaning up.
losetup | grep -q . && umount $(losetup | awk -F: '{ print $1}')
losetup | grep -q . && losetup -d $(losetup | awk -F: '{ print $1}')

echo "Recording all file system changes..." | tee /dev/tty1
sync 2>&1 | tee /dev/tty1
echo "done." | tee /dev/tty1

# Exit
( echo ""; echo "System update succeeded." ) | tee /dev/tty1
do_exit
