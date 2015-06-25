%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : web site to allow the target configuration
Name            : mect_cfg_website
Version         : 0.0.1
Release         : 1
License         : GPL
Vendor          : Mect s.r.l
Packager        : Emiliano Bergamaschini
Group           : Mect s.r.l
Source          : %{name}-%{version}.tar.bz2
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT/%{pfx} all

%Install
make DESTDIR=$RPM_BUILD_ROOT/%{pfx} install

%Clean
make DESTDIR=$RPM_BUILD_ROOT/%{pfx} clean

%Files
%defattr(-,root,root)
%{pfx}/*

