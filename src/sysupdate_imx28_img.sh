#!/bin/sh

# Execution trace
set -x

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
expr "$RELEASE" : @@THIS_VERSION_MAJ_MIN@@ > /dev/null || expr "$RELEASE" : 3\\.0 > /dev/null || expr "$RELEASE" : 2\\.0 > /dev/null || do_exit "cannot update the installed version ${RELEASE}."

# Check if we have an update for the running target.
UPDIMG="${MNTDIR}/img_sysupdate-@@THIS_VERSION@@-${TARGET}.ext2"
test -r "$UPDIMG" || do_exit "cannot find an update for ${TARGET}."

# Set up the temporary directory.
mkdir -p "$MYTMPDIR"
test -d "$MYTMPDIR" || do_exit "cannot create temporary direcctory ${MYTMPDIR}."
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
#

echo "Updating the $TARGET to version @@THIS_VERSION@@." | tee /dev/tty1
echo "" | tee /dev/tty1

# Update the kernel.
if test -s ${IMGDIR}/${SUDIR}/imx28_ivt_linux.sb; then
	test -x ${IMGDIR}/${SUDIR}/kobs-ng || do_exit "cannot find ${IMGDIR}/${SUDIR}/kobs-ng."

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

# Save password file (for root password) and authorized_keys (for public ssh keys).
cp "${PASSWDDIR}/${PASSWD}" "$MYTMPDIR"
cp /etc/dropbear/authorized_keys "$MYTMPDIR/authorized_keys"

# root file system is now mounted RW, see /etc/rc.d/init.d/S10setup
rsync -aHc --exclude "$SUDIR" --exclude local ${IMGDIR}/ / 2>&1 | tee /dev/tty1
/sbin/ldconfig -r / 2>&1 | tee /dev/tty1

if test -s "${PASSWDDIR}/${PASSWD}"; then
    sed -i '/^root:/ d' "${PASSWDDIR}/${PASSWD}"
    if test "$( grep ^root: ${PASSWDDIR}/${PASSWD} | wc -l )" = "0"; then
        grep ^root: "${MYTMPDIR}/${PASSWD}" >> "${PASSWDDIR}/${PASSWD}"
        test "$( grep ^root: ${PASSWDDIR}/${PASSWD} | wc -l )" = "1" || echo "cannot preserve root password." | tee /dev/tty1
    else
        echo "cannot preserve root password." | tee /dev/tty1
    fi
fi
sed -i '/root@vpndev.vpn-smily.com/ d' "$MYTMPDIR/authorized_keys"
cat "$MYTMPDIR/authorized_keys" >> /etc/dropbear/authorized_keys

echo "done." | tee /dev/tty1

# Update the local file system.
if test -d ${IMGDIR}/local; then
	echo "Updating the local file system..." | tee /dev/tty1
	rsync -aHc ${IMGDIR}/local/ /local/ 2>&1 | tee /dev/tty1
	echo "done." | tee /dev/tty1
fi

# Cleaning up.
losetup | grep -q . && umount $(losetup | awk -F: '{ print $1}')
losetup | grep -q . && losetup -d $(losetup | awk -F: '{ print $1}')

if expr "$RELEASE" : '3\.0\.1' > /dev/null; then
    test -f /etc/rsync-mect.pwd && rm -f /etc/rsync-mect.pwd
    test -f /local/var/spool/cron/crontabs/root.default && rm -f /local/var/spool/cron/crontabs/root.default
    test -f /local/var/spool/cron/crontabs/root && rm -f /local/var/spool/cron/crontabs/root
    test -f /usr/sbin/rsync-mect.sh && rm -f /usr/sbin/rsync-mect.sh
fi

echo "Recording all file system changes..." | tee /dev/tty1
sync 2>&1 | tee /dev/tty1
echo "done." | tee /dev/tty1

# Exit
( echo ""; echo "System update succeeded." ) | tee /dev/tty1
do_exit
