%define base %(echo %{_prefix} | sed -e s,/usr.*$,,)
%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : A small executable that replaces many UNIX utilities
Name            : busybox
Version         : 1.15.0
Release         : 1
License         : GPL
URL             : http://www.busybox.net/
Vendor          : Freescale
Packager        : Steve Papacharalambous/Stuart Hughes
Group           : System Environment/Shells
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed busybox for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Shells
AutoReqProv     : no

%Description rfs
busybox package contents restricted to just the files that are
needed at run time on the target.


%Description
%{summary}


%Prep
export LC_ALL
LC_ALL=C

%setup -T -c -n %{name}
cd ..; rmdir %{name}; ln -s ../../../projects/%{name} %{name}


%Build
export LC_ALL
LC_ALL=C

PKG_BUSYBOX_PRECONFIG=${PKG_BUSYBOX_PRECONFIG:-busybox.config}
if [ -f "$PLATFORM_PATH/${PKG_BUSYBOX_PRECONFIG}" ]
then
    cp $PLATFORM_PATH/$PKG_BUSYBOX_PRECONFIG .config
else
    if [ -f "$CONFIG_DIR/defaults/$PKG_BUSYBOX_PRECONFIG" ]
    then
        cp "$CONFIG_DIR/defaults/$PKG_BUSYBOX_PRECONFIG"  .config
    fi
fi
if [ -n "$PKG_BUSYBOX_WANT_CF" -o -n "$SCB_WANT_CF" ]
then
    make menuconfig HOSTCC="$BUILDCC"
    cp .config $PLATFORM_PATH/$PKG_BUSYBOX_PRECONFIG
else
    yes "" | make config HOSTCC="$BUILDCC"
fi
if [ "$GNUTARCH" = m68knommu ]
then
    MAKE_EXTRA="SKIP_STRIP=y"
fi
make HOSTCC="$BUILDCC" $MAKE_EXTRA


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
install -d $RPM_BUILD_ROOT/%{pfx}/%{base}/bin
make HOSTCC="$BUILDCC" CONFIG_PREFIX=$RPM_BUILD_ROOT/%{pfx}/%{base} install
for i in pidof ip
do
    
    if [ -f $RPM_BUILD_ROOT/%{pfx}/%{base}/bin/$i ]
    then
        rm $RPM_BUILD_ROOT/%{pfx}/%{base}/bin/$i
        ln -sf ../bin/busybox $RPM_BUILD_ROOT/%{pfx}/%{base}/sbin/$i
    fi
done
install -d $RPM_BUILD_ROOT/%{pfx}/%{base}/etc/rc.d/init.d
for i in run log
do
    install -d $RPM_BUILD_ROOT/%{pfx}/%{base}/var/$i
done
touch $RPM_BUILD_ROOT/%{pfx}/%{base}/var/run/utmp
touch $RPM_BUILD_ROOT/%{pfx}/%{base}/var/log/wtmp
cat <<EOF > $RPM_BUILD_ROOT/%{pfx}/%{base}/etc/busybox.conf
[SUID]
su = ssx root.root
passwd = ssx root.root
EOF
chmod 644 $RPM_BUILD_ROOT/%{pfx}/%{base}/etc/busybox.conf


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/bin/addgroup
%{pfx}/bin/adduser
%{pfx}/bin/ash
%{pfx}/bin/busybox
%{pfx}/bin/cat
%{pfx}/bin/catv
%{pfx}/bin/chgrp
%{pfx}/bin/chmod
%{pfx}/bin/chown
%{pfx}/bin/cp
%{pfx}/bin/date
%{pfx}/bin/dd
%{pfx}/bin/delgroup
%{pfx}/bin/deluser
%{pfx}/bin/df
%{pfx}/bin/dmesg
%{pfx}/bin/dnsdomainname
%{pfx}/bin/echo
%{pfx}/bin/egrep
%{pfx}/bin/false
%{pfx}/bin/fgrep
%{pfx}/bin/getopt
%{pfx}/bin/grep
%{pfx}/bin/gunzip
%{pfx}/bin/gzip
%{pfx}/bin/hostname
%{pfx}/bin/kill
%{pfx}/bin/ln
%{pfx}/bin/login
%{pfx}/bin/ls
%{pfx}/bin/mkdir
%{pfx}/bin/mknod
%{pfx}/bin/more
%{pfx}/bin/mount
%{pfx}/bin/mv
%{pfx}/bin/nice
%{pfx}/bin/ping
%{pfx}/bin/ps
%{pfx}/bin/pwd
%{pfx}/bin/rm
%{pfx}/bin/rmdir
%{pfx}/bin/sed
%{pfx}/bin/sh
%{pfx}/bin/sleep
%{pfx}/bin/stty
%{pfx}/bin/su
%{pfx}/bin/sync
%{pfx}/bin/tar
%{pfx}/bin/touch
%{pfx}/bin/true
%{pfx}/bin/umount
%{pfx}/bin/uname
%{pfx}/bin/usleep
%{pfx}/bin/vi
%{pfx}/bin/watch
%{pfx}/bin/zcat
%{pfx}/etc/busybox.conf
%{pfx}/etc/rc.d/init.d
%{pfx}/sbin/adjtimex
%{pfx}/sbin/depmod
%{pfx}/sbin/devmem
%{pfx}/sbin/fdisk
%{pfx}/sbin/getty
%{pfx}/sbin/halt
%{pfx}/sbin/hwclock
%{pfx}/sbin/ifconfig
%{pfx}/sbin/init
%{pfx}/sbin/insmod
%{pfx}/sbin/klogd
%{pfx}/sbin/logread
%{pfx}/sbin/losetup
%{pfx}/sbin/lsmod
%{pfx}/sbin/mdev
%{pfx}/sbin/mkdosfs
%{pfx}/sbin/mkfs.vfat
%{pfx}/sbin/modprobe
%{pfx}/sbin/pidof
%{pfx}/sbin/poweroff
%{pfx}/sbin/reboot
%{pfx}/sbin/rmmod
%{pfx}/sbin/route
%{pfx}/sbin/start-stop-daemon
%{pfx}/sbin/sysctl
%{pfx}/sbin/syslogd
%{pfx}/sbin/udhcpc
%{pfx}/usr/bin/[
%{pfx}/usr/bin/[[
%{pfx}/usr/bin/awk
%{pfx}/usr/bin/basename
%{pfx}/usr/bin/bunzip2
%{pfx}/usr/bin/bzcat
%{pfx}/usr/bin/bzip2
%{pfx}/usr/bin/cal
%{pfx}/usr/bin/chvt
%{pfx}/usr/bin/cksum
%{pfx}/usr/bin/cut
%{pfx}/usr/bin/diff
%{pfx}/usr/bin/dirname
%{pfx}/usr/bin/dos2unix
%{pfx}/usr/bin/du
%{pfx}/usr/bin/env
%{pfx}/usr/bin/expr
%{pfx}/usr/bin/find
%{pfx}/usr/bin/free
%{pfx}/usr/bin/ftpget
%{pfx}/usr/bin/ftpput
%{pfx}/usr/bin/head
%{pfx}/usr/bin/hexdump
%{pfx}/usr/bin/hostid
%{pfx}/usr/bin/id
%{pfx}/usr/bin/install
%{pfx}/usr/bin/killall
%{pfx}/usr/bin/length
%{pfx}/usr/bin/logger
%{pfx}/usr/bin/logname
%{pfx}/usr/bin/mesg
%{pfx}/usr/bin/mkfifo
%{pfx}/usr/bin/od
%{pfx}/usr/bin/openvt
%{pfx}/usr/bin/passwd
%{pfx}/usr/bin/printf
%{pfx}/usr/bin/readlink
%{pfx}/usr/bin/renice
%{pfx}/usr/bin/resize
%{pfx}/usr/bin/seq
%{pfx}/usr/bin/sort
%{pfx}/usr/bin/tail
%{pfx}/usr/bin/tee
%{pfx}/usr/bin/telnet
%{pfx}/usr/bin/test
%{pfx}/usr/bin/tftp
%{pfx}/usr/bin/top
%{pfx}/usr/bin/tr
%{pfx}/usr/bin/tty
%{pfx}/usr/bin/uniq
%{pfx}/usr/bin/unix2dos
%{pfx}/usr/bin/unzip
%{pfx}/usr/bin/uptime
%{pfx}/usr/bin/uudecode
%{pfx}/usr/bin/uuencode
%{pfx}/usr/bin/wc
%{pfx}/usr/bin/who
%{pfx}/usr/bin/yes
%{pfx}/usr/sbin/chroot
%{pfx}/usr/sbin/crond
%{pfx}/usr/sbin/ftpd
%{pfx}/usr/sbin/inetd
%{pfx}/usr/sbin/rdate
%{pfx}/usr/sbin/telnetd
%{pfx}/var/log/wtmp
%{pfx}/var/run/utmp
