%define pfx /opt/freescale/rootfs/%{_target_cpu}
Summary         : Freescale vpu-wrapper library
Name            : libfslvpuwrap 
Version         : 1.0.28
Release         : 1
License         : LGPL
Vendor          : Freescale Semiconductor
Packager        : Sario Hu
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

./configure --prefix=%{_prefix} --host=$CFGHOST \
	    --build=%{_build} 
make

%Install
rm -rf $RPM_BUILD_ROOT

make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}/

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
