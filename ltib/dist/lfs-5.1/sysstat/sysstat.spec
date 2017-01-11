%define pfx /opt/freescale/rootfs/%{_target_cpu}
%define __os_install_post %{nil}

Summary         : System performance tools for Linux
Name            : sysstat
Version         : 8.1.2
Release         : 2
License         : GPL
Vendor          : Freescale
Packager        : John Rigby
Group           : Systems Administration
Source          : %{name}_%{version}.orig.tar.gz
Patch1          : %{name}_%{version}-%{release}.diff.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup -n %{name}-%{version}
%patch1 -p1

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make

%Install
rm -rf $RPM_BUILD_ROOT
make install IGNORE_MAN_GROUP=y DESTDIR=$RPM_BUILD_ROOT/%{pfx}

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
