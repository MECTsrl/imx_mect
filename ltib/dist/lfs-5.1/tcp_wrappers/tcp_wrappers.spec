%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : A security tool which acts as a wrapper for TCP daemons
Name            : tcp_wrappers
Version         : 7.6
Release         : 1
License         : Distributable
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : System Environment/Daemons
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed %{name} for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Daemons
AutoReqProv     : no

%Description rfs
%{name} package contents restricted to just the files that
are needed at run time on the target.


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

if [ -n "$UCLIBC" ]
then 
    make REAL_DAEMON_DIR=/usr/sbin STYLE=-DPROCESS_OPTIONS linux-uclibc
else
    make REAL_DAEMON_DIR=/usr/sbin STYLE=-DPROCESS_OPTIONS linux
fi


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
for i in sbin lib include
do
    install -m 755 -d $RPM_BUILD_ROOT/%{pfx}/usr/$i
done
for i in man3 man5 man8
do
    install -m 755 -d $RPM_BUILD_ROOT/%{pfx}/usr/share/man/$i
done
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}%{_libdir}/libwrap.so
%{pfx}%{_libdir}/libwrap.so.0
%{pfx}%{_libdir}/libwrap.so.0.7.6
%{pfx}%{_sbindir}/safe_finger
%{pfx}%{_sbindir}/tcpd
%{pfx}%{_sbindir}/tcpdchk
%{pfx}%{_sbindir}/tcpdmatch
%{pfx}%{_sbindir}/try-from
