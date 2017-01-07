%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : PDF Render Library
Name            : poppler
Version         : 0.11.3
Release         : 0
License         : GNU GPL
Vendor          : Freescale
Packager        : Andre Silva / Rogerio Pimentel
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
URL             : http://poppler.freedesktop.org/poppler-0.11.3.tar.gz

%Description
%{summary}

%Prep
%setup

%Build

./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} --disable-gtk-test

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
