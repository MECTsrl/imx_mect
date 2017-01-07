%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Global Locate GPS driver
Name            : gl-gps
Version         : 1.2.3
Release         : 0
License         : Proprietary
Vendor          : Broadcom Corporation
Packager        : Sam Yang
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}-%{version}
Prefix          : %{pfx}
%Description
This package provides proprietary binary kernel modules, libraries, and
test code built from Global Locate GPS-B driver. It's for Linux Kernel 2.6.31 version.


%{summary}

%Prep
%setup

%Build

%Install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}
cp -a etc usr $RPM_BUILD_ROOT/%{pfx}

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
