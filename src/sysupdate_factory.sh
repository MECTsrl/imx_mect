#!/bin/sh

#sysupdate_factory: Same as sysupdate_imx28_img but only restore Simple application like does Cloner

# Execution trace
# set -x

SYSTMPDIR="/tmp"
WORKDIR="$(dirname $0)"
FACTORY_IMG=${WORKDIR}/_ysupdate_factory_@@THIS_VERSION@@.ext2
IMGDIR="/tmp/sysupdate"
RAMDIR="/tmp/ramdisk"

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

# Stop most of the running processes and watchdog.
/etc/rc.d/init.d/autoexec stop
/etc/rc.d/init.d/crond stop
/etc/rc.d/init.d/boa stop
#/etc/rc.d/init.d/inetd stop
/sbin/devmem 0x80056008 32 0x00000010

# Collect info on installed system
#

# Mect Suite version
RELEASE="`awk '/^Release/ { print $2; }' /rootfs_version`"
test -n "$RELEASE" || do_exit "cannot find the installed version."

# Target system type
TARGET="`awk '/^Target/ { print $2; }' /rootfs_version`"
test -n "$TARGET" || do_exit "cannot find the system type."

# Check the compatibility of the update with the installed version (Only whitin current Version).
if [ $RELEASE != '@@THIS_VERSION@@' ]; then
   do_exit "cannot update the installed version ${RELEASE} with @@THIS_VERSION@@."
fi

#Board Serial Number 
SNFILE="/etc/serial.conf"
if test -s "$SNFILE"; then
	SN="$(cat "$SNFILE")"
	echo "Board Serial Number: ${SN}"  | tee /dev/tty1
fi

# Checking SD Card and umount Swap File if present
sd_mount_point="/local/sd_card"
SWAP_FILE="$sd_mount_point/swap/swap_file"
sd_device_path="/dev/mmcblk0"
if [ -e $sd_device_path ]; then
   echo "Found an SD Raw Device: $sd_device_path" | tee /dev/tty1
   SD_PRESENT=`mount|grep $sd_mount_point`
   if test -n "$SD_PRESENT"  ; then
      echo "Found an ext3 SD card mounted: $sd_mount_point" | tee /dev/tty1
      if [ -e "$SWAP_FILE" ]; then
         echo "Stop Swap File" | tee /dev/tty1
         swapoff $SWAP_FILE
      else
         echo "No Swap file present" | tee /dev/tty1
      fi
      echo "Umount SD Card $sd_mount_point" | tee /dev/tty1
      umount $sd_mount_point
   else
      echo "No SD card mounted" | tee /dev/tty1
   fi
else
   echo "No SD card detected" | tee /dev/tty1
fi

#remount root_fs in ro mode
mount -o remount,ro /

# Check presence of ext2 file
test -e "$FACTORY_IMG"  || do_exit "cannot find ext2 file ${FACTORY_IMG}."

# Prepare sysupdate image mount point.
test -d "$IMGDIR" && rm -rf "$IMGDIR"
mkdir -p "$IMGDIR"
test -d "$IMGDIR" || do_exit "cannot create image mount directory ${IMGDIR}."

# Mount the sysupdate image.
losetup | grep -q . && losetup -d $(losetup | awk -F: '{ print $1}')
mount -o ro,loop "$FACTORY_IMG" "$IMGDIR" || do_exit "*** ERROR: cannot mount  image ${CLONEIMG}."

# Check if we have an update for the running target.
UPDIMG="${IMGDIR}/Simples/${TARGET}_ms@@THIS_VERSION@@/localfs.tar"
test -r "$UPDIMG" || do_exit "cannot find an update for ${TARGET}."

echo "Found local archive for target $TARGET" | tee /dev/tty1
echo "" | tee /dev/tty1

#create Ram Disk to expand localfs.tar
test -d "$RAMDIR" && rm -rf "$RAMDIR"
mkdir -p "$RAMDIR"
test -d "$RAMDIR" || do_exit "cannot create ram disk directory ${RAMDIR}."
mount -t tmpfs -o size=48M tmpfs $RAMDIR || do_exit "*** ERROR: cannot mount  ram disk ${CLONEIMG}."

#expanding  localfs.tar
echo "Expanding: $UPDIMG"  | tee /dev/tty1
tar xf $UPDIMG -C $RAMDIR 2>&1 | tee /dev/tty1
echo "" | tee /dev/tty1

# Update the local file system.
# FIX: Come gestire gli Exclude di Cloner --exclude hmi*
echo "Restoring  @@THIS_VERSION@@ Simple Application on the $TARGET." | tee /dev/tty1
echo "" | tee /dev/tty1

# Update the local file system.
if find $RAMDIR -mindepth 1 -maxdepth 1 | read; then
   echo "Updating the local file system..." | tee /dev/tty1
   rsync -Havxc --delete --exclude .ssh --exclude flash/root/fcrts --exclude flash/etc/sysconfig/net.conf --exclude flash/etc/wpa_supplicant/default.conf --exclude flash/etc/ppp --exclude var/spool/cron/crontabs/root --exclude flash/data/alarms --exclude sd_card ${RAMDIR}/ /local/  2>&1 
   echo "" | tee /dev/tty1
else
   do_exit "*** ERROR: ${RAMDIR} is Empty!"
fi

echo "Recording all file system changes..." | tee /dev/tty1
sync 2>&1 | tee /dev/tty1
echo "done." | tee /dev/tty1

# Exit
( echo ""; echo "System update succeeded." ) | tee /dev/tty1
do_exit
