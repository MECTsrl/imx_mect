#!/bin/sh -x

# create a new sysupdate:
# 1. update UPDATEABLE_VERSIONS
# 2. run make_sysupdate.sh
#

# from /etc/rc.d/init.d/S10setup
mntdir=/tmp/mnt

do_exit()
{
	sync 2>&1 | tee /dev/tty1
	echo "******************************************" | tee /dev/tty1
	echo "* Please power off and remove the usbkey *" | tee /dev/tty1
	echo "******************************************" | tee /dev/tty1
	while true; do read -rp ""; done
}

# stop as much as possible
/etc/rc.d/init.d/autoexec stop
/etc/rc.d/init.d/crond stop
/etc/rc.d/init.d/boa stop
/etc/rc.d/init.d/inetd stop

eval `grep Target /rootfs_version | awk '{print "TARGET="$2}'`
echo "Starting update to version @@THIS_VERSION@@ (on target $TARGET)" | tee /dev/tty1

# check the running version
UPDATEABLE_VERSIONS="2.0rc4 2.0.1 2.0.2 2.0.3 2.0.5 2.0.6 2.0.7 2.0.8 2.0.9 2.0.9rc4 2.0.9rc5 2.0.9rc6 2.0.9rc7 2.0.9rc8 2.0.9rc9"
if [ ! -f /rootfs_version ]
then
	echo SYSUPDATE ERROR: unknown root filesystem. | tee /dev/tty1
	do_exit
fi
OK=0
eval `grep Release /rootfs_version | awk '{print "RELEASE="$2}'`
for version in $UPDATEABLE_VERSIONS
do
	if [ "$version" = "$RELEASE" ]
	then
		OK=1
	fi
done
if [ $OK = 0 ]
then
	echo SYSUPDATE ERROR: cannot update $RELEASE. | tee /dev/tty1
	do_exit
fi

# extract (uudecode) the update archive into the usb key
echo Extracting the update archive ... | tee /dev/tty1
uudecode $0 2>&1 | tee /dev/tty1
echo done. 2>&1 | tee /dev/tty1

# expanding (tar x) the update archive into the usb key
if [ ! -s ${mntdir}/update.tar.gz ]
then
	echo SYSUPDATE ERROR: cannot find any update archive | tee /dev/tty1
	do_exit
fi
echo Expanding the update archive ... | tee /dev/tty1
tar xzf ${mntdir}/update.tar.gz -C ${mntdir}/ 2>&1 | tee /dev/tty1
rm -f ${mntdir}/update.tar.gz 2>&1 | tee /dev/tty1
echo done. 2>&1 | tee /dev/tty1

# check the update content wrt the running target
if [ ! -d ${mntdir}/${TARGET} ]
then
	echo SYSUPDATE ERROR: cannot find any update content for ${TARGET} | tee /dev/tty1
	# don't know how to clean the usb key
	do_exit
fi

# kernel update
if [ -e ${mntdir}/${TARGET}/imx28_ivt_linux.sb ]
then
	echo Updating the Linux kernel ... | tee /dev/tty1
	if [ ! -x ${mntdir}/kobs-ng ]
	then
		echo SYSUPDATE ERROR: cannot find "${mntdir}/kobs-ng" | tee /dev/tty1
		do_exit
	fi
	flash_eraseall /dev/mtd0  2>&1 | tee /dev/tty1
	${mntdir}/kobs-ng init ${mntdir}/${TARGET}/imx28_ivt_linux.sb 2>&1 | tee /dev/tty1
	rm -f ${mntdir}/kobs-ng 2>&1 | tee /dev/tty1
	echo done. 2>&1 | tee /dev/tty1
fi

# rootfs update
if [ -e ${mntdir}/${TARGET}/rootfs.tar ]
then
	echo Updating the root filesystem ... | tee /dev/tty1
	# we already are in rw mode, see /etc/rc.d/init.d/S10setup
	tar xf ${mntdir}/${TARGET}/rootfs.tar -C / 2>&1 | tee /dev/tty1
	/sbin/ldconfig -r / 2>&1 | tee /dev/tty1
	echo done. 2>&1 | tee /dev/tty1
fi

# localfs update
if [ -e ${mntdir}/${TARGET}/localfs.tar ]
then
	echo Updating the local filesystem ... | tee /dev/tty1
	tar xf ${mntdir}/${TARGET}/localfs.tar -C /local 2>&1 | tee /dev/tty1
	echo done. 2>&1 | tee /dev/tty1
fi

# usb key cleanup
rm -rf ${mntdir}/${TARGET}

# exiting
echo ""  | tee /dev/tty1
echo "SYSUPDATE DONE" | tee /dev/tty1
do_exit
