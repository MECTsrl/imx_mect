%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : language and system independent CORBA interfaces for creating reusable components and compound documents
Name            : libbonobo
Version         : 2.24.0
Release         : 1
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar.bz2
License         : LGPL/GPL
Patch1          : libbonobo-2.24.0-rm-configure-gthread-check.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup
%patch1 -p1

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make ORBIT_IDL=/usr/bin/orbit-idl-2

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
rm -f $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/*.la

%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*
