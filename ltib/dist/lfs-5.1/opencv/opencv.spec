%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : The Open Computer Vision Library (Intel)
Name            : opencv
Version         : 1.1.0
Release         : 0
License         : BSD
Vendor          : Freescale
Packager        : Andre Silva
Group           : System Environment/Libraries
URL             : http://opencv.willowgarage.com
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} \
 --without-python --disable-apps --with-gstreamer --with-gtk
make

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
find $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/ -name "*.la" | xargs rm -f

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
