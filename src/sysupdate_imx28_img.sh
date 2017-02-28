#!/bin/sh

# Execution trace
set -x

MNTDIR="/tmp/mnt"               # Set in /etc/rc.d/init.d/S10setup
IMGDIR="/tmp/sysupdate"
SUDIR="sysupdate"               # sysupdate-specific dir within the image

trap cleanup EXIT
cleanup()
{
        cd /

        sleep 2                 # Wait for programs to terminate.

        losetup | grep -q . && umount $(losetup | awk -F: '{ print $1}')
        losetup | grep -q . && losetup -d $(losetup | awk -F: '{ print $1}')

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

# Stop most of the running processes.
/etc/rc.d/init.d/autoexec stop
/etc/rc.d/init.d/crond stop
/etc/rc.d/init.d/boa stop
/etc/rc.d/init.d/inetd stop

# Collect info on installed system
#

# Image version
RELEASE="`awk '/^Release/ { print $2; }' /rootfs_version`"
test -n "$RELEASE" || do_exit "cannot find the installed version."

# Target system type
TARGET="`awk '/^Target/ { print $2; }' /rootfs_version`"
test -n "$TARGET" || do_exit "cannot find the system type."

# Check the compatibility of the update with the installed version.
expr "$RELEASE" : @@THIS_VERSION_MAJ_MIN@@ > /dev/null || do_exit "cannot update the installed version ${RELEASE}."

# Check if we have an update for the running target.
UPDIMG="${MNTDIR}/img_sysupdate-@@THIS_VERSION@@-${TARGET}.ext2"
test -r "$UPDIMG" || do_exit "cannot find an update for ${TARGET}."

# Clean idle setups.
losetup | grep -q . && losetup -d $(losetup | awk -F: '{ print $1}')

# Prepare sysupdate image mount point.
test -d "$IMGDIR" && rm -rf "$IMGDIR"
mkdir -p "$IMGDIR"
test -d "$IMGDIR" || do_exit "cannot create image directory ${IMGDIR}."

# Mount the sysupdate image.
mount -o ro,loop "$UPDIMG" "$IMGDIR" || do_exit "cannot mount cloner image ${CLONEIMG}."

# Start the update.
#

echo "Updating the $TARGET to version @@THIS_VERSION@@." | tee /dev/tty1
echo "" | tee /dev/tty1

# Update the kernel.
if test -s ${IMGDIR}/${SUDIR}/imx28_ivt_linux.sb; then
	test -x ${IMGDIR}/${SUDIR}/kobs-ng || do_exit "cannot find \"${IMGDIR}/${SUDIR}/kobs-ng.\""

	echo "Updating the Linux kernel..." | tee /dev/tty1
	if test "$TARGET" = TPAC1006; then
		flash_eraseall -q /dev/mtd0 2>&1 | tee /dev/tty1
	else
		flash_eraseall /dev/mtd0 2>&1 | tee /dev/tty1
	fi
	${IMGDIR}/${SUDIR}/kobs-ng init ${IMGDIR}/${SUDIR}/imx28_ivt_linux.sb 2>&1 | tee /dev/tty1
	echo "done." | tee /dev/tty1
fi

# Update the root file system.
echo "Updating the root file system..." | tee /dev/tty1
# root file system is now mounted RW, see /etc/rc.d/init.d/S10setup
rsync -a --exclude "$SUDIR" --exclude local --inplace ${IMGDIR}/ / 2> /dev/null | tee /dev/tty1
rsync -a --exclude "$SUDIR" --exclude local ${IMGDIR}/ / 2>&1 | tee /dev/tty1
/sbin/ldconfig -r / 2>&1 | tee /dev/tty1
echo "done." | tee /dev/tty1

# Update the local file system.
if test -d ${IMGDIR}/local; then
	echo "Updating the local file system..." | tee /dev/tty1
	rsync -a --inplace ${IMGDIR}/local/ /local/ 2> /dev/null | tee /dev/tty1
	rsync -a ${IMGDIR}/local/ /local/ 2>&1 | tee /dev/tty1
	echo "done." | tee /dev/tty1
fi

# Cleaning up.
losetup | grep -q . && umount $(losetup | awk -F: '{ print $1}')
losetup | grep -q . && losetup -d $(losetup | awk -F: '{ print $1}')

echo "Recording all file system changes..." | tee /dev/tty1
sync 2>&1 | tee /dev/tty1
echo "done." | tee /dev/tty1

# Exit
( echo ""; echo "System update succeeded." ) | tee /dev/tty1
do_exit
