%define pfx /opt/freescale/rootfs/%{_target_cpu}
Summary         : Gstreamer Freescale Plugin
Name            : gst-plugins-gl
Version         : 0.10.3.1
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
./configure --disable-libvisual --prefix=%{_prefix} --host=$CFGHOST \
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
