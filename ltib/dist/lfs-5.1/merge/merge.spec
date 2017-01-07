%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Merge files for an embedded root filesystem
Name            : merge
Version         : 0.1
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Steve Papacharalambous/Stuart Hughes
Group           : System Environment/Utilities
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
# We assume that the user knows the dependencies of the merge file(s).
Autoreqprov     : no


%Package rfs
Summary         : Trimmed merge for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Utilities
AutoReqProv     : no

%Description rfs
merge package contents restricted to just the files that are
needed at run time on the target on the root file system.

%Package lfs
Summary         : Trimmed merge for local file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Utilities
Prefix          : %{pfx}/local
AutoReqProv     : no

%Description lfs
merge package contents restricted to just the files that are
needed at run time on the target on the local file system.


%Description
If a merge directory is detected at the top level of the
root file system builder directory, it creates an RPM with
the structure and files of the merge directory.  This allows
the user to directly add files and directories to the target
root file system.


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

mkdir -p $RPM_BUILD_ROOT/%{pfx}/etc
chmod 755 $RPM_BUILD_ROOT/%{pfx}/etc

touch $RPM_BUILD_ROOT/%{pfx}/etc/ltib-release
chmod 666 $RPM_BUILD_ROOT/%{pfx}/etc/ltib-release

for dir in "$PLATFORM_PATH/merge" "$TOP/merge"; do
    if test -d $dir; then
        cd $dir
        find . -name CVS -prune -o -perm -444 ! -type b ! -type c -print0 2>/dev/null | cpio -p0d --quiet $RPM_BUILD_ROOT%{pfx}
        cd -
    fi
done

# Set execution permissions (discarded by VCS).
for f in \
	/etc/rc.d/init.d/autoexec \
	/etc/rc.d/init.d/boa \
	/etc/rc.d/init.d/crond \
	/etc/rc.d/init.d/iptables \
	/etc/rc.d/init.d/mac_sn \
	/etc/rc.d/init.d/network \
	/etc/rc.d/init.d/openvpn \
	/etc/rc.d/init.d/S10setup \
	/etc/rc.d/init.d/sdcheck \
	/etc/rc.d/init.d/setup \
	/etc/rc.d/rc.local \
	/local/bin/rsync-mect.sh \
	/local/etc/ppp/ip-down \
	/local/etc/ppp/ip-up \
	/usr/bin/fcrts.sh \
	/usr/sbin/usb3g.sh \
	/usr/sbin/wifi.sh \
; do
	chmod 755 $RPM_BUILD_ROOT%{pfx}$f
done

# Symlink /etc/resolv.conf in the RW /local file system.
( cd $RPM_BUILD_ROOT%{pfx}/etc; ln -sf /local/etc/resolv.conf )

# Symlink /etc/ppp in the RW /local file system.
( cd $RPM_BUILD_ROOT%{pfx}/etc; ln -sf /local/etc/ppp )


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/etc/asound.conf
%{pfx}/etc/conf/boa.conf
%{pfx}/etc/dhclient.conf
%{pfx}/etc/fstab
%{pfx}/etc/group
%{pfx}/etc/inetd.conf
%{pfx}/etc/iptables.default
%{pfx}/etc/ltib-release
%{pfx}/etc/mdev.conf
%{pfx}/etc/passwd
%{pfx}/etc/ppp
%{pfx}/etc/profile
%{pfx}/etc/rc.d/init.d/autoexec
%{pfx}/etc/rc.d/init.d/boa
%{pfx}/etc/rc.d/init.d/crond
%{pfx}/etc/rc.d/init.d/iptables
%{pfx}/etc/rc.d/init.d/mac_sn
%{pfx}/etc/rc.d/init.d/network
%{pfx}/etc/rc.d/init.d/openvpn
%{pfx}/etc/rc.d/init.d/S10setup
%{pfx}/etc/rc.d/init.d/sdcheck
%{pfx}/etc/rc.d/init.d/setup
%{pfx}/etc/rc.d/rc.local
%{pfx}/etc/resolv.conf
%{pfx}/etc/services
%{pfx}/usr/bin/fcrts.sh
%{pfx}/usr/sbin/usb3g.sh
%{pfx}/usr/sbin/wifi.sh

%Files lfs
%defattr(-,root,root)
%{pfx}/local/bin/rsync-mect.sh
%{pfx}/local/etc/icinga/nrpe.cfg
%{pfx}/local/etc/ppp/chat-usb3g
%{pfx}/local/etc/ppp/ip-down
%{pfx}/local/etc/ppp/ip-up
%{pfx}/local/etc/ppp/peers/usb3g
%{pfx}/local/etc/resolv.conf
%{pfx}/local/etc/sysconfig/brightness
%{pfx}/local/etc/sysconfig/lang_table.csv
%{pfx}/local/etc/sysconfig/net.conf
%{pfx}/local/root/make_usb_device
%{pfx}/local/var/spool/cron/crontabs/root
