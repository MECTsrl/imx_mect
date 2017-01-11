%define pfx /opt/freescale/rootfs/%{_target_cpu}
Summary         : Freescale plugin for alsalib
Name            : fsl-alsa-plugins
Version         : 1.0.25
Release         : 1
License         : LGPL
Vendor          : Freescale Semiconductor
Packager        : Wayne Feng
Group           : Applications/System
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
export PKG_CONFIG="`which pkg-config` --static "
export BBB="`which autoconf`"
echo ${BBB}
./configure --prefix=%{_prefix} --host=$CFGHOST \
	    --build=%{_build} CFLAGS=-I"$DEV_IMAGE/usr/src/linux/include"
make

%Install
rm -rf $RPM_BUILD_ROOT

make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}/

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
