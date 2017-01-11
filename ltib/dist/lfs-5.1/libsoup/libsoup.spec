%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Libsoup is an HTTP library implementation in C.
Name            : libsoup
Version         : 2.26.3
Release         : 1
Vendor          : Freescale
Packager        : Rob Herring
Group           : Development/Libraries
Source          : %{name}-%{version}.tar.bz2
License         : LGPL
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup 

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} --without-gnome
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
