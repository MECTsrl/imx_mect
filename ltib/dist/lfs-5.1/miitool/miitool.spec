%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Data Test Program
Name            : mii-tool
Version         : 1.9.1.1
Release         : 1
License         : GPL
Vendor          : Donald Becker
Packager        : Hake Huang
Group           : Applications/System
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
URL             : http://www.sfr-fresh.com/unix/privat/

%Description
%{summary}

%Prep
%setup

%Build
make

%Install
rm -rf $RPM_BUILD_ROOT
install -d $RPM_BUILD_ROOT/%{pfx}/usr/bin
install mii-tool $RPM_BUILD_ROOT/%{pfx}/usr/bin

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*

