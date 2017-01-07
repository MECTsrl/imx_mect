%define base %(echo %{_prefix} | sed -e s,/usr.*$,,)
%define pfx /opt/freescale/rootfs/%{_target_cpu}
%define verrel 050330

Summary         : Advanced IP routing and network device configuration tools
Name            : iproute
Version         : 2.6.37
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Jaksa Djordjevic, Stuart Hughes
Group           : Applications/System
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no

# iproute-2.6.37-1317825720.patch : exclude arpd from compilation cause db_185.h problems


%Package rfs
Summary         : Trimmed iproute for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no

%Description rfs
iproute package contents restricted to just the files that
are needed at run time on the target.


%Description
%{summary}

The iproute package contains networking utilities (ip and rtmon, for
example) which are designed to use the advanced networking
capabilities of the Linux kernel.


%Prep
export LC_ALL
LC_ALL=C

%setup -T -c -n %{name}
cd ..; rmdir %{name}; ln -s ../../../projects/%{name} %{name}


%Build
export LC_ALL
LC_ALL=C

make -j1 KERNEL_INCLUDE=$DEV_IMAGE/usr/src/linux HOSTCC="$BUILDCC"


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make -j1 install SBINDIR=%{base}/sbin DESTDIR=$RPM_BUILD_ROOT/%{pfx}


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/etc/iproute2/ematch_map
%{pfx}/etc/iproute2/rt_dsfield
%{pfx}/etc/iproute2/rt_protos
%{pfx}/etc/iproute2/rt_realms
%{pfx}/etc/iproute2/rt_scopes
%{pfx}/etc/iproute2/rt_tables
%{pfx}/lib/tc
%{pfx}/sbin/ctstat
%{pfx}/sbin/genl
%{pfx}/sbin/ifcfg
%{pfx}/sbin/ifstat
%{pfx}/sbin/ip
%{pfx}/sbin/lnstat
%{pfx}/sbin/nstat
%{pfx}/sbin/routef
%{pfx}/sbin/routel
%{pfx}/sbin/rtacct
%{pfx}/sbin/rtmon
%{pfx}/sbin/rtpr
%{pfx}/sbin/rtstat
%{pfx}/sbin/ss
%{pfx}/sbin/tc
%{pfx}/usr/lib/tc/experimental.dist
%{pfx}/usr/lib/tc/normal.dist
%{pfx}/usr/lib/tc/pareto.dist
%{pfx}/usr/lib/tc/paretonormal.dist
%{pfx}/var/lib/arpd
