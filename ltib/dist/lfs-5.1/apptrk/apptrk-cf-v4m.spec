%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Embedded GNU Linux Userspace debug agent for CF CodeWarrior
Name            : AppTRK-Base
Version         : 1.37
Release         : 1
License         : Freescale EULA
Vendor          : Freescale
Packager        : Tudor Stanescu
Group           : Development/Debuggers
Source          : %{name}-%{version}.tar.gz
Patch1          : apptrk-1.37-coldfire-v4m.patch
Patch2          : apptrk-1.37-coldfire-linux-target.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup 
%patch1 -p1
%patch2 -p1

%Build
make all

%Install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}/usr/bin
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
