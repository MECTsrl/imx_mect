%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : ELF prelinking utility to speed up dynamic linking.
Name            : prelink
Version         : 20130503
Release         : 1
License         : GPLv2+
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System/Tools
URL             : https://people.redhat.com/jakub/prelink/
Source          : %{name}-%{version}.tar.bz2
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup -n %{name}

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
