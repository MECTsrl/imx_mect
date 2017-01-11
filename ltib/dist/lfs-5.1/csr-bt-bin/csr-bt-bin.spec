%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : CSR bluetooch BCHS4 binary 
Name            : csr-bt-bin
Version         : 1.2.0
Release         : 0
License         : Proprietary
Vendor          : CSR Ltd.
Packager        : Sam Yang
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}-%{version}
Prefix          : %{pfx}
%Description
This package provides proprietary binary libraries and
test code built from CSR bc4-15.3.13. It provides bluetooth A2DP/SPP/FTP profiles support. Hardware is APM6628 chip in 3stack board. 

%{summary}

%Prep
%setup

%Build

%Install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}
cp -a usr $RPM_BUILD_ROOT/%{pfx}

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
