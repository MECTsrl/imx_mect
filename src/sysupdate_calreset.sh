#!/bin/sh
mntdir=/tmp/mnt

chvt 1
dd if=/dev/zero of=/dev/fb0 > /dev/null 2>&1
echo "+-----------------------------------------------------+" | tee /dev/tty1
echo "|                                                     |" | tee /dev/tty1
echo "|              ResetCal: WORK IN PROGRESS             |" | tee /dev/tty1
echo "|                                                     |" | tee /dev/tty1
echo "+-----------------------------------------------------+" | tee /dev/tty1
echo "" | tee /dev/tty1
date
echo -n "1) checking filesystem version ... " | tee /dev/tty1
if test -r /rootfs_version; then
	echo "Mect Suite" | tee /dev/tty1
	echo -n "2) stopping Mect Suite application ... " | tee /dev/tty1
	killall splash
	sleep 2
	echo "ok" | tee /dev/tty1
	echo -n "3) stopping watchdog ... " | tee /dev/tty1
	/sbin/devmem 0x80056008 32 0x00000010
	echo "ok" | tee /dev/tty1
	echo -n "4) removing screen calibration file ... " | tee /dev/tty1
	rm -f /etc/pointercal
	sync
	echo "removed" | tee /dev/tty1
	echo -n "5) remounting rootfs in ro mode... " | tee /dev/tty1
	mount -o remount,ro /
	echo "ok" | tee /dev/tty1
else
	echo "Freescale" | tee /dev/tty1
	echo -n "2) removing screen calibration file ... " | tee /dev/tty1
	rm -f /local/etc/sysconfig/pointercal
	echo "removed" | tee /dev/tty1
fi


echo "" | tee /dev/tty1
echo "" | tee /dev/tty1
echo "+-----------------------------------------------------+" | tee /dev/tty1
echo "|      Screen Pointer Calibration reset done          |" | tee /dev/tty1
echo "|                                                     |" | tee /dev/tty1
echo "| Please power off and remove the USB storage device. |" | tee /dev/tty1
echo "|                                                     |" | tee /dev/tty1
echo "|     Calibration will start at next power on         |" | tee /dev/tty1
echo "+-----------------------------------------------------+" | tee /dev/tty1

sync
umount $mntdir

while true; do read -rp "" dummy; done

exit 0
