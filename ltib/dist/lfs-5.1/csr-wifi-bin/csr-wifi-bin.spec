%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : CSR wifi driver binary
Name            : csr-wifi-bin
Version         : 4.3.0
Release         : 1
License         : Proprietary
Vendor          : CSR
Packager        : Sam Yang
Group           : System/Servers
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build

%Install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}
cp -rf * $RPM_BUILD_ROOT/%{pfx}
pwd
ls

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(755,root,root)
%{pfx}/*
