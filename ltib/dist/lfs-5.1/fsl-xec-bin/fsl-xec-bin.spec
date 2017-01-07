%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : freescale xec binary
Name            : fsl-xec-bin
Version         : 2.6.35.3
Release         : 1.1.0
License         : Proprietary
Vendor          : Freescale
Packager        : Katherine Lu
Group           : System/Servers
Source          : %{name}-%{version}-%{release}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup -n %{name}-%{version}-%{release}

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
