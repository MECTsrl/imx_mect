%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : System-wide profiler for Linux systems
Name            : oprofile
Version         : 0.9.6
Release         : 1
License         : GPL
URL             : http://oprofile.sourceforge.net/download/
Vendor          : Freescale
Packager        : Stuart Hughes/WMSG
Group           : Development/Tools
Source          : %{name}-%{version}.tar.gz
Patch0          : %{name}-fix-build-error-in-gcc-4.6.3.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
BuildRequires   : popt, binutils

%Description
%{summary}

Note:
binutils is required for libbfd only
This only support 2.6 kernels

%Prep
%setup 
%patch0 -p1

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} \
            --with-kernel-support \
            --config-cache --mandir=%{_mandir} \
            --with-binutils=$DEV_IMAGE/usr
make

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
