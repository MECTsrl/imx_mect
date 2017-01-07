%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : GPU driver and app for mx50
Name            : amd-gpu-bin-mx50
Version         : 10.08.00
Release         : 1
License         : Proprietary
Vendor          : AMD
Packager        : Zhou Jie
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
