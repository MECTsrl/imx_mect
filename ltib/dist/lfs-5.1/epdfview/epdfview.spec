%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : PDF reader
Name            : epdfview
Version         : 0.1.7
Release         : 0
License         : GNU GPL
Vendor          : Freescale
Packager        : Rogerio Pimentel
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar.bz2
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
URL             : http://trac.emma-soft.com/epdfview/chrome/site/releases/epdfview-0.1.7.tar.bz2

%Description
%{summary}

%Prep
%setup

%Build

./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}

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
