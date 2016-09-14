#!/bin/sh

# Execution trace
set -x

# Set in /etc/rc.d/init.d/S10setup
mntdir=/tmp/mnt

# Non-empty string means exit upon error.
do_exit()
{
	sync 2>&1 | tee /dev/tty1

	test -n "$1" && echo "SYSUPDATE ERROR: $1" | tee /dev/tty1
	echo "" | tee /dev/tty1
	echo "****************************************************" | tee /dev/tty1
	echo "* Please power off and remove the USB memory stick *" | tee /dev/tty1
	echo "****************************************************" | tee /dev/tty1

	while true; do
		read -rp ""
	done

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
if test -z "$RELEASE"; then
	do_exit "cannot find the installed version."
fi

# Target system type
TARGET="`awk '/^Target/ { print $2; }' /rootfs_version`"
if test -z "$TARGET"; then
	do_exit "cannot find the system type."
fi

# Compatibility with the installed version
if ! expr "$RELEASE" : 2\\.0 > /dev/null; then
	do_exit "cannot update installed version ${RELEASE}."
fi

# Start the update.
#

echo "Updating the $TARGET to version @@THIS_VERSION@@." | tee /dev/tty1

# Extract (uudecode) the update archive from the USB stick.
echo "Extracting the update archive..." | tee /dev/tty1
uudecode $0 2>&1 | tee /dev/tty1
if ! test -s ${mntdir}/update.tar.gz; then
	do_exit "update archive extraction failed."
fi
echo "done." | tee /dev/tty1

# Expand (tar x) the update archive into the usb stick
rm -rf ${mntdir}/${TARGET}
echo "Expanding the update archive..." | tee /dev/tty1
tar xzf ${mntdir}/update.tar.gz -C ${mntdir} 2>&1 | tee /dev/tty1
rm -f ${mntdir}/update.tar.gz
echo "done." | tee /dev/tty1

# Check if we have an update for the running target.
if ! test -d ${mntdir}/${TARGET}; then
	# TODO: extract under a specific directory on the USB
	# stick and remove that directory here.
	do_exit "cannot find an update for ${TARGET}."
fi

# Update the kernel.
if test -s ${mntdir}/${TARGET}/imx28_ivt_linux.sb; then
	if ! test -x ${mntdir}/kobs-ng; then
		do_exit "cannot find \"${mntdir}/kobs-ng.\""
	fi

	echo "Updating the Linux kernel..." | tee /dev/tty1
	flash_eraseall /dev/mtd0 2>&1 | tee /dev/tty1
	${mntdir}/kobs-ng init ${mntdir}/${TARGET}/imx28_ivt_linux.sb 2>&1 | tee /dev/tty1
	rm -f ${mntdir}/kobs-ng
	echo "done." | tee /dev/tty1
fi

# Update the root file system.
if test -s ${mntdir}/${TARGET}/rootfs.tar; then
	echo "Updating the root file system..." | tee /dev/tty1
	# We already are in RW mode, see /etc/rc.d/init.d/S10setup
	tar xf ${mntdir}/${TARGET}/rootfs.tar -C / 2>&1 | tee /dev/tty1
	/sbin/ldconfig -r / 2>&1 | tee /dev/tty1
	echo "done." | tee /dev/tty1
fi

# Update the local file system.
if test -s ${mntdir}/${TARGET}/localfs.tar; then
	echo "Updating the local file system..." | tee /dev/tty1
	tar xf ${mntdir}/${TARGET}/localfs.tar -C /local 2>&1 | tee /dev/tty1
	echo "done." | tee /dev/tty1
fi

# Clean the USB memory stick.
rm -rf ${mntdir}/${TARGET}

# Exit
echo "" | tee /dev/tty1
echo "System updated successfully." | tee /dev/tty1
do_exit

