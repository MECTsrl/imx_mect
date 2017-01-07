%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : GPU driver and app for x11 on mx50
Name            : amd-gpu-x11-bin-mx50
Version         : 10.08.00
Release         : 1
License         : Proprietary
Vendor          : AMD
Packager        : Zhou Jie
Group           : System/Servers
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
URL             : git://sw-git01-tx30/git/sw_git/repos/linux-amd-gpu.git

%Description
%{summary}

%Prep
%setup

%Build

%Install
rm -rf $RPM_BUILD_ROOT
install -d $RPM_BUILD_ROOT/%{pfx}
cp -rf * $RPM_BUILD_ROOT/%{pfx}

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(755,root,root)
%{pfx}/*
