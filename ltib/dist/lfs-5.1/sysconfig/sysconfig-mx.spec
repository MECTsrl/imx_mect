%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary		: System configuration package
Name		: sysconfig
Version		: 1.2
Release		: 5
License		: GPL
Vendor		: Freescale
Packager	: Stuart Hughes
Group		: System Environment/Base
Source          : inittab
BuildRoot	: %{_tmppath}/%{name}
Prefix		: %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed sysconfig for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Base
AutoReqProv     : no

%Description rfs
sysconfig package contents restricted to just the files that
are needed at run time on the target.


%Description
%{summary}

%Prep
export LC_ALL
LC_ALL=C


%Build
export LC_ALL
LC_ALL=C


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

mkdir -p $RPM_BUILD_ROOT/%{pfx}/etc/rc.d

test  "$SYSCFG_START_SYSLOG"        =  "y"  &&  syslog=syslog
test  "$SYSCFG_START_UDEV"          =  "y"  &&  udev=udev
test  "$SYSCFG_START_MDEV"          =  "y"  &&  mdev=mdev
test  "$SYSCFG_START_DEVFSD"        =  "y"  &&  devfsd=devfsd
test  "$SYSCFG_START_NETWORK"       =  "y"  &&  network=network
test  "$SYSCFG_START_INETD"         =  "y"  &&  inetd=inetd
test  "$SYSCFG_START_PORTMAP"       =  "y"  &&  portmap=portmap
test  "$SYSCFG_START_DROPBEAR_SSH"  =  "y"  &&  dropbear=dropbear
test  "$SYSCFG_START_SSHD"          =  "y"  &&  sshd=sshd
test  "$SYSCFG_START_BOA"           =  "y"  &&  boa=boa
test  "$SYSCFG_START_VSFTPD"        =  "y"  &&  vsftpd=vsftpd
test  "$SYSCFG_SETTIME"             =  "y"  &&  settime=settime
test  "$SYSCFG_START_DHCPD"         =  "y"  &&  dhcpd=dhcp
test  "$SYSCFG_START_SAMBA"         =  "y"  &&  smb=smb
test  "$SYSCFG_START_WATCHDOG"      =  "y"  &&  watchdog=watchdog
test  "$SYSCFG_START_GTK2"          =  "y"  &&  gtk2=gtk2
test  "$SYSCFG_START_PANGO"         =  "y"  &&  pango=pango
test  "$SYSCFG_START_FSLGNOME"      =  "y"  &&  fslgnome=fslgnome
test  "$SYSCFG_START_S10SETUP"      =  "y"  &&  S10setup=S10setup
test  "$SYSCFG_START_OPENVPN"       =  "y"  &&  openvpn=openvpn
if test "$SYSCFG_START_AUTOEXEC" = "y"; then
        autoexec=autoexec
	sdcheck=sdcheck
	usbmode=usbmode
fi

if test "$SYSCFG_START_TELNET" = "y"; then
	telnetd=telnetd

	mkdir -p $RPM_BUILD_ROOT/%{pfx}/etc/rc.d/init.d

	cat <<EOF > $RPM_BUILD_ROOT/%{pfx}/etc/rc.d/init.d/telnetd
#!/bin/sh

test -x /usr/sbin/telnetd || exit 0

if test "$1" = "stop" -o "$1" = "restart"; then
	echo "Stopping the telnet daemon: "
	killall telnetd
fi

if test "$1" = "start" -o "$1" = "restart"; then
	echo "Starting the telnet daemon: "
	/usr/sbin/telnetd
fi
EOF
	chmod +x $RPM_BUILD_ROOT/%{pfx}/etc/rc.d/init.d/telnetd
fi

cat <<EOF > $RPM_BUILD_ROOT/%{pfx}/etc/rc.d/rc.conf
all_services="mount-proc-sys mdev udev hostname devfsd depmod modules filesystems sdcheck syslog network iptables inetd portmap setup dropbear sshd boa vsftpd smb dhcpd settime fslgnome watchdog bluetooth gtk2 pango telnetd usbmode S10setup autoexec openvpn crond"
all_services_r="crond openvpn autoexec S10setup usbmode telnetd pango gtk2 bluetooth watchdog fslgnome settime dhcpd smb vsftpd boa sshd dropbear setup portmap inetd iptables network syslog sdcheck filesystems modules depmod devfsd hostname udev mdev mount-proc-sys"

cfg_services="mount-proc-sys $mdev $udev hostname $devfsd depmod modules filesystems $usbmode $network iptables $inetd $portmap setup $sdcheck $autoexec $dropbear $sshd $boa $vsftpd $telnetd $syslog $smb $dhcpd $settime $fslgnome $watchdog $bluetooth $gtk2 $pango $S10setup $openvpn crond"
cfg_services_r="crond $openvpn $autoexec $sdcheck $S10setup $usbmode $pango $gtk2 $bluetooth $watchdog $fslgnome $settime $dhcpd $smb $syslog $telnetd $vsftpd $boa $sshd $dropbear setup $portmap $inetd iptables $network filesystems modules depmod $devfsd hostname $udev $mdev mount-proc-sys"

export HOSTNAME="${SYSCFG_HOSTNAME:-$PLATFORM}"
export NTP_SERVER="$SYSCFG_NTP_SERVER"
export MODLIST="$SYSCFG_MODLIST"
export RAMDIRS="$SYSCFG_RAM_DIRS"
export TMPFS="$SYSCFG_TMPFS"
export TMPFS_SIZE="${SYSCFG_TMPFS_SIZE:-512k}"
export READONLY_FS="$SYSCFG_READONLY_FS"
export INETD_ARGS="$SYSCFG_INETD_ARGS"
export BOA_ARGS="$SYSCFG_BOA_ARGS"
export SMBD_ARGS="${SYSCFG_SMBD_ARGS}"
export NMBD_ARGS="${SYSCFG_NMBD_ARGS}"
export DHCP_ARG="${SYSCFG_DHCP_ARG}"
export DEPLOYMENT_STYLE="${SYSCFG_DEPLOYMENT_STYLE:-NFS}"
export SYSCFG_DHCPC_CMD="${SYSCFG_DHCPC_CMD:-udhcpc -b -i }"
export DROPBEAR_ARGS="${SYSCFG_DROPBEAR_ARGS}"
EOF

# network interfaces
for i in 0 1 2 3 4 5
do
    if [  "$(eval echo \$$(echo SYSCFG_IFACE$i))" = "y" ]
    then
	if [ "$(eval echo \$$(echo SYSCFG_DHCPC$i))" = "y" ]
	then
	    cat <<EOF >> $RPM_BUILD_ROOT/%{pfx}/etc/rc.d/rc.conf
# net interface $i
export $(echo SYSCFG_IFACE$i)=y
export $(echo INTERFACE$i)="$(eval echo \$$(echo SYSCFG_NET_INTERFACE$i))"
export $(echo IPADDR$i)="dhcp"
EOF
	else
	    cat <<EOF >> $RPM_BUILD_ROOT/%{pfx}/etc/rc.d/rc.conf
# net interface $i
export $(echo SYSCFG_IFACE$i)=y
export $(echo INTERFACE$i)="$(eval echo \$$(echo SYSCFG_NET_INTERFACE$i))"
export $(echo IPADDR$i)="$(eval echo \$$(echo SYSCFG_IPADDR$i))"
export $(echo NETMASK$i)="$(eval echo \$$(echo SYSCFG_NET_MASK$i))"
export $(echo BROADCAST$i)="$(eval echo \$$(echo SYSCFG_NET_BROADCAST$i))"
export $(echo GATEWAY$i)="$(eval echo \$$(echo SYSCFG_NET_GATEWAY$i))"
export $(echo NAMESERVER$i)="$(eval echo \$$(echo SYSCFG_NAMESERVER$i))"
EOF
	fi
    fi
done

if test "$PKG_BUSYBOX" = "y" -a "$PKG_SYSVINIT" != "y"; then
    # BusyBox init
    if test "$SYSCFG_WANT_LOGIN_TTY" = "y"; then
	sys_login=`echo "$SYSCFG_LOGING_TTY" | sed 's/\\\\\\\\n/\n/'`
    else
	sys_login="::respawn:-/bin/sh"
    fi
    install -m 644 %{SOURCE0} $RPM_BUILD_ROOT/%{pfx}/etc/inittab
else
    # SysVInit
    if test "$SYSCFG_WANT_LOGIN_TTY" = "y"; then
	run_level=3
    else
	run_level=1
    fi
    cat <<EOF > $RPM_BUILD_ROOT/%{pfx}/etc/inittab
id:$run_level:initdefault:

si::sysinit:/etc/rc.d/rcS start

# Runlevel 0 is halt
# Runlevel 1 is single-user
# Runlevels 2-5 are multi-user
# Runlevel 6 is reboot

l0:0:wait:/etc/rc.d/rcS stop
l1:1:respawn:/bin/sh -i
l6:6:wait:/sbin/reboot

co:2345:respawn:${SYSCFG_LOGING_TTY:-$INITTAB_LINE}

ca::ctrlaltdel:/sbin/reboot
EOF
fi

cat <<EOF > $RPM_BUILD_ROOT/%{pfx}/etc/issue

$(gcc --version | grep gcc)
root filesystem built on $(date -R)
MECT s.r.l. http://www.mect.it/

EOF

# The kernel attempts to run /init (not /sbin/init!) from initramfs images
test "$SYSCFG_DEPLOYMENT_STYLE" = "INITRAMFS" && ln -s /sbin/init $RPM_BUILD_ROOT/%{pfx}/init

%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/etc/inittab
%{pfx}/etc/issue
%{pfx}/etc/rc.d/rc.conf

%Files rfs
%defattr(-,root,root)
%{pfx}/etc/inittab
%{pfx}/etc/issue
%{pfx}/etc/rc.d/rc.conf
