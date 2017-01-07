%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Manufactory Update Application
Name            : uuc
Version         : 2.6.35.3
Release         : 1.1.0
License         : GPL
Vendor          : Freescale
Packager        : Frank Li
Group           : Development/Tools
URL             : http://xxxx
Source          : %{name}-%{version}-%{release}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup -n %{name}-%{version}-%{release}

%Build
make

%Install
rm -rf $RPM_BUILD_ROOT
make install DEST_DIR=$RPM_BUILD_ROOT/%{pfx}

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
