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
expr "$RELEASE" : 3\\.1\\.5 > /dev/null || do_exit "cannot update the installed version ${RELEASE}, only 3.1.5 is supported."

# Start the update.
#

echo "Hardening the $TARGET." | tee /dev/tty1
echo "" | tee /dev/tty1

echo "1/3 adding the jolly public key ..." | tee /dev/tty1
sed -i '/xFieeICN3L4w== jolly_key/ d' /etc/dropbear/authorized_keys
echo "ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAACAQDG1i2RQG1JuB1rV7NewZ5PJjxAryC8/NzQHqhJBgL/vdD/y1nV++wCJzFKV8vQEs4tTP0u0orUUJfnzmY7VKNiC0UKb9XXg8b0hx1EYfEajmNIi2BM8gY0hPGywehPgTUqw21jXtOT9Fg6l/1GsOkfUjnYhLrrIAV4LMxBWO+yJSrBNZdt4D5TKjT77PysrJGi0HpFK66ZxgNnZAJme23pDEuwho8kWK0cTuiqnwjpbDNwZBCgnQb70mDdxVNzyYzXcCzkYeuI/LKMTapjqei8W6nxCmsEJCT7dhPloU5fBpgidFH9HGmFg3H1bJAbgWv/nvS2XF8Xfwp/41VoedgEqnQJjbVHjCewaxlsyCIV/efg0RBYh5pvkaO5uvh/BoBX3FHba4GzNlAuHtfYjm3kynVYmDhKg6Q7aR1GUGQ6nU6aunxRubqwwZyUwt6F0AwLeYN0/VHxiaQ4z8aI9+CdO69HZ79+kNPSfr1tahxsuOtfK6AGak3U9ORtwFDPZKwGN7IS8XX5H7+t0lLX420Gge7JeIOzG2wSgajGFGY0qmwZ2G7uF3H/Z2m62npIQvmVe1mIi7BKPf3bcckHEuyiOJ0vazfXHbwGcgjs1v8s/4cOf++yws8dh1Qsh/NM+I2S3PE3sdXs0+aGOyk7suoZe6vww+/lCLxFieeICN3L4w== jolly_key" >> /etc/dropbear/authorized_keys
echo "done." | tee /dev/tty1

echo "2/3 disabling password logins ..." | tee /dev/tty1
sed -i 's/dropbear *-i *$/dropbear -i -s/' /etc/inetd.conf
echo "done." | tee /dev/tty1

echo "3/3 activating iptables firewall ..." | tee /dev/tty1
cat << EOF > /etc/iptables
*filter
:INPUT DROP [0:0]
:FORWARD ACCEPT [0:0]
:OUTPUT ACCEPT [18:2180]
-A INPUT -i lo -j ACCEPT

# enabled services

# SSH
-A INPUT -p tcp -m tcp --dport 22 -j ACCEPT
-A INPUT -p tcp -m tcp --sport 22 -j ACCEPT

# HTTP
-A INPUT -p tcp -m tcp --dport 80 -j ACCEPT 

# Modbus TCP Server
-A INPUT -p tcp -m tcp --dport 502 -j ACCEPT

# VNC :0
-A INPUT -p tcp -m tcp --dport 5900 -j ACCEPT

# ATCMControl_RunTimeSystem control
-A INPUT -p tcp -m tcp --dport 17290 -j ACCEPT

# OpenVPN smily
-A INPUT -p tcp -m tcp --sport 443 -j ACCEPT
-A INPUT -p udp -m udp --sport 53 -j ACCEPT

# ICMP ping
-A INPUT -p icmp --icmp-type 0 -j ACCEPT
-A INPUT -p icmp --icmp-type 8 -j ACCEPT

# DHCP
-A INPUT -p udp -m udp --sport 67 -j ACCEPT
-A INPUT -p udp -m udp --dport 68 -j ACCEPT

# HTTP per allarmi
-A INPUT -p tcp -m tcp --sport 8080 -j ACCEPT

# disabled services

# NRPE
#-A INPUT -p tcp -m tcp --dport 5666 -j ACCEPT

# Telnet
#-A INPUT -p tcp -m tcp --dport 23 -j ACCEPT

COMMIT
EOF
echo "done." | tee /dev/tty1

echo "Recording all file system changes..." | tee /dev/tty1
sync 2>&1 | tee /dev/tty1
echo "done." | tee /dev/tty1

# Exit
( echo ""; echo "System update succeeded." ) | tee /dev/tty1
do_exit
