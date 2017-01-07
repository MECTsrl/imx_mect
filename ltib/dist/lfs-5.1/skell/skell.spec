%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Skelleton files for an embedded root filesystem
Name            : skell
Version         : 1.18
Release         : 2
License         : GPL
Vendor          : Freescale
Packager        : Steve Papacharalambous/Stuart Hughes
Group           : System Environment/Utilities
Source          : %{name}-%{version}.tar.gz
Source2         : rootfs_patch-1.2.tar.bz2
Source3         : skell-local-1.6.tar.bz2
Source4         : gdbserver
Patch1          : skell-1.18-dropbear_args.patch
Patch2          : skell-1.18-imx.patch
Patch3          : skell-1.18-imx-fsl-gstplugin.patch
Patch4          : skell-1.19-imx-fsl-gnome.patch
Patch5          : skell-1.19-imx-hal-messagebus.patch
Patch6          : skell-1.18-mect-config.patch
Patch7          : skell-1.18-1317731895.patch
Patch8          : skell-1.18-1318337638.patch
Patch9          : skell-1.18-1319030600.patch
Patch10         : skell-1.18-1328695400.patch
Patch11         : skell-1.18-1329225205.patch
Patch14         : skell-1.18-1349102220.patch
Patch16         : skell-1.18-1416848812.patch
Patch17         : skell-1.18-1418999072.patch
Patch18         : skell-1.18-1420825964.patch
Patch19         : skell-1.18-1421745467.patch
Patch20         : skell-1.18-1421838801.patch
Patch21         : skell-1.18-1423222246.patch
Patch22         : skell-1.18-1427985138.patch
Patch23         : skell-1.18-1428680350.patch
Patch24         : skell-1.18-1429172043.patch
Patch25         : skell-1.18-1431590614.patch
Patch26         : skell-1.18-mect-ld-xenomai-libs.patch
Patch27         : skell-1.18-mect-remove-inittab.patch
Patch28         : skell-1.18-mect-remove-issue.patch
Patch29         : skell-1.18-mect-remove-rc.local.patch
Patch31         : skell-mect-dev-fixes-in-init.d.patch
Patch32         : skell-1.18-1448375293.patch
Patch33         : skell-1.18-1448558592.patch
Patch34         : skell-1.18-1453482173.patch
Patch35         : skell-1.18-1453824311.patch
Patch36         : skell-1.18-remove_resolv_conf.patch
Patch37         : skell-1.18-remove_network.patch
Patch38         : skell-1.18-remove_mdev_conf.patch
Patch39         : skell-1.18-remove_sdcheck.patch
Patch40         : skell-1.18-remove_net_conf.patch
Patch41         : skell-1.18-limit_to_skell_creation.patch
Patch42         : skell-1.18-remove_home_dir.patch
Patch43         : skell-1.18-create_local_and_its_tree.patch
Patch44         : skell-1.18-create_local_update.patch
Patch45         : skell-1.18-move_etc_profile_to_merge.patch
Patch46         : skell-1.18-remove_boa_rc_script.patch
Patch47         : skell-1.18-no_fstab.patch
Patch48         : skell-1.18-remove_passwd_group.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no

# skell-1.18-mect-config.patch : prepare a skell with read only partition and data partition
# skell-1.18-1317731895.patch  : add the environment variable for touchscreen and QT, remove rc.conf because is already created by sysconfig package
# skell-1.18-1318337638.patch  : disable httpd and create the character device /dev/buzzer
# skell-1.18-1328695400.patch  : add the autoexec script
# skell-1.18-1329225205.patch  : fix the LCD calibration sync problem, add the MAC configuration at power-on
#Patch12          : skell-1.18-1332342531.patch add S10setup script to file system 
#Patch13          : skell-1.18-1333039892.patch modified S10setup script
#Patch14          : skell-1.18-1349102220.patch modified S10setup script, added root password
#Patch15          : skell-1.18-1353931133.patch modified S10setup script
#Patch16          : skell-1.18-1355479713.patch modified S10setup to work with the autoexec logic. Added S10setup and autoexec in /usr/bin
#Patch22          : skell-1.18-1427985138.patch remove the unecessary sleep at boot scripts and change the command to detect the usb
#Patch25          : skell-1.18-1431590614.patch set the backglight first of all into the autoexec script


%Package rfs
Summary         : Trimmed skell for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Utilities
AutoReqProv     : no

%Description rfs
skell package contents restricted to just the files that are
needed at run time on the target.

%Package lfs
Summary         : Skeleton for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Utilities
Prefix          : %{pfx}/local
AutoReqProv     : no

%Description lfs
Basic contents of the local file system.


%Description
%{summary}


%Prep
export LC_ALL
LC_ALL=C

%setup
%patch1 -p1
%patch2 -p1
%patch3 -p1
%patch4 -p1
%patch5 -p1
%patch6 -p1
%patch7 -p1
%patch8 -p1
%patch9 -p1
%patch10 -p1
%patch11 -p1
%patch14 -p1
%patch16 -p1
%patch17 -p1
%patch18 -p1
%patch19 -p1
%patch20 -p1
%patch21 -p1
%patch22 -p1
%patch23 -p1
%patch24 -p1
%patch25 -p1
%patch26 -p1
%patch27 -p1
%patch28 -p1
%patch29 -p1
%patch31 -p1
%patch32 -p1
%patch33 -p1
%patch34 -p1
%patch35 -p1
%patch36 -p1
%patch37 -p1
%patch38 -p1
%patch39 -p1
%patch40 -p1
%patch41 -p1
%patch42 -p1
%patch43 -p1
%patch44 -p1
%patch45 -p1
%patch46 -p1
%patch47 -p1
%patch48 -p1


%Build
export LC_ALL
LC_ALL=C

DESTDIR=$RPM_BUILD_ROOT/%{pfx} 


%Install
export LC_ALL
LC_ALL=C

DESTDIR=$RPM_BUILD_ROOT/%{pfx} 

rm -rf $RPM_BUILD_ROOT

make DESTDIR=$RPM_BUILD_ROOT/%{pfx} install

test -z "$PKG_SKELL_WANT_TERMINFO" && rm -rf $RPM_BUILD_ROOT/%{pfx}%{_prefix}/share/terminfo

tar xjvf %{SOURCE2} -C $RPM_BUILD_ROOT/%{pfx}
tar xjvf %{SOURCE3} -C $RPM_BUILD_ROOT/%{pfx}
install -m 755 -D %{SOURCE4} $RPM_BUILD_ROOT/%{pfx}%{_bindir}/`basename %{SOURCE4}`


%Clean
export LC_ALL
LC_ALL=C

sudo rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/bin
%{pfx}/control
%{pfx}/dev
%{pfx}/etc/devfsd.conf
%{pfx}/etc/exports
%{pfx}/etc/host.conf
%{pfx}/etc/hosts
%{pfx}/etc/hosts.allow
%{pfx}/etc/hosts.deny
%{pfx}/etc/inputrc
%{pfx}/etc/issue.net
%{pfx}/etc/ld.so.conf
%{pfx}/etc/mime.types
%{pfx}/etc/modprobe.conf
%{pfx}/etc/nsswitch.conf
%{pfx}/etc/printcap
%{pfx}/etc/protocols
%{pfx}/etc/rc.d/init.d/depmod
%{pfx}/etc/rc.d/init.d/devfsd
%{pfx}/etc/rc.d/init.d/dhcp
%{pfx}/etc/rc.d/init.d/dhcpd
%{pfx}/etc/rc.d/init.d/dropbear
%{pfx}/etc/rc.d/init.d/filesystems
%{pfx}/etc/rc.d/init.d/hostname
%{pfx}/etc/rc.d/init.d/inetd
%{pfx}/etc/rc.d/init.d/mdev
%{pfx}/etc/rc.d/init.d/modules
%{pfx}/etc/rc.d/init.d/mount-proc-sys
%{pfx}/etc/rc.d/init.d/portmap
%{pfx}/etc/rc.d/init.d/settime
%{pfx}/etc/rc.d/init.d/smb
%{pfx}/etc/rc.d/init.d/sshd
%{pfx}/etc/rc.d/init.d/syslog
%{pfx}/etc/rc.d/init.d/udev
%{pfx}/etc/rc.d/init.d/usbmode
%{pfx}/etc/rc.d/rc.modules
%{pfx}/etc/rc.d/rcS
%{pfx}/etc/rc.d/rc.serial
%{pfx}/etc/securetty
%{pfx}/etc/shadow
%{pfx}/etc/shells
%{pfx}/etc/sysctl.conf
%{pfx}/etc/udhcpd.conf
%{pfx}/lib/modules
%{pfx}/local/control
%{pfx}/local/data/alarms
%{pfx}/local/data/customstore
%{pfx}/local/data/recipe
%{pfx}/local/data/store
%{pfx}/local/data/trends
%{pfx}/local/root
%{pfx}/local/sd_card
%{pfx}/local/update
%{pfx}/mnt/cdrom
%{pfx}/mnt/floppy
%{pfx}/mnt/nfs
%{pfx}/mnt/rwfs
%{pfx}/mnt/src
%{pfx}/opt
%{pfx}/proc
%{pfx}/root
%{pfx}/sbin
%{pfx}/sys
%{pfx}/tmp
%{pfx}/update
%{pfx}/usr/bin/gdbserver
%{pfx}/usr/bin/sign
%{pfx}/usr/bin/stop
%{pfx}/usr/lib
%{pfx}/usr/share/udhcpc/default.script
%{pfx}/var/ftp/bin
%{pfx}/var/ftp/etc
%{pfx}/var/ftp/lib
%{pfx}/var/ftp/pub
%{pfx}/var/lib
%{pfx}/var/lock
%{pfx}/var/log/lastlog
%{pfx}/var/mail
%{pfx}/var/run
%{pfx}/var/spool/lpd
%{pfx}/var/spool/mail
%{pfx}/var/tmp
%{pfx}/var/www/cgi-bin/test_cgi
%{pfx}/var/www/html/index.html
%{pfx}/var/www/icons

%Files lfs
%defattr(-,root,root)
%{pfx}/local/control
%{pfx}/local/data/alarms
%{pfx}/local/data/customstore
%{pfx}/local/data/recipe
%{pfx}/local/data/store
%{pfx}/local/data/trends
%{pfx}/local/retentive
%{pfx}/local/root
%{pfx}/local/sd_card
%{pfx}/local/update
