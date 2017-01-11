%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : A library for Ogg multimedia container format
Name            : libogg
Version         : 1.1.4
Release         : 1
License         : BSD
Vendor          : Freescale
Packager        : Fabio Estevam
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
URL             : http://downloads.xiph.org/releases/ogg/libogg-1.1.4.tar.gz

%Description
%{summary}

%Prep
%setup

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} --mandir=%{_mandir}
make

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
rm -f $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/*.la

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
