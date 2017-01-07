%define pfx /opt/freescale/rootfs/%{_target_cpu}
%define pkg_name libIDL

Summary         : Corba Interface Definition Language interface files
Name            : libIDL
Version         : 0.8.11
Release         : 1
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : Development/Libraries
Source          : %{pkg_name}-%{version}.tar.bz2
License         : LGPL
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup -n %{pkg_name}-%{version}

%Build
export libIDL_cv_long_long_format=yes
./configure --prefix=%{_prefix} --host=$CFGHOST
make

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
rm -f $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/*.la

%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*
