%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : GPU driver and app for x11 on mx51
Name            : amd-gpu-x11-bin-mx51
Version         : 2.6.35.3
Release         : 1.1.0
License         : Proprietary
Vendor          : AMD
Packager        : Richard Zhao
Group           : System/Servers
Source          : %{name}-%{version}-%{release}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
URL             : git://sw-git01-tx30/git/sw_git/repos/linux-amd-gpu.git

%Description
%{summary}

%Prep
%setup -n %{name}-%{version}-%{release}

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
