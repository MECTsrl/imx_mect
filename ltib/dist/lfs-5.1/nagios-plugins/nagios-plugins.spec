%define pfx /opt/freescale/rootfs/%{_target_cpu}
%define mb_name check_modbus
%define mb_vers 0.46

Summary         : Host/service/network monitoring plugins for Nagios
Name            : nagios-plugins
Version         : 1.0
Release         : 1
License         : GPL
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
Source          : %{mb_name}-%{mb_vers}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed %{name} for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
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

# Timestamp order is important.
for f in configure.ac configure.in aclocal.m4 configure config.h.in Makefile.am Makefile.in; do
	find . -name $f -exec touch {} \;
done
cd %{mb_name}-%{mb_vers}
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

cd %{mb_name}-%{mb_vers}
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
%{pfx}/usr/bin/check_modbus
