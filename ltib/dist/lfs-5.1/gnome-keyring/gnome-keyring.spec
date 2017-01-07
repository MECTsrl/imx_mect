%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Daemon that keeps passwords and other secrets for users. 
Name            : gnome-keyring
Version         : 2.24.1
Release         : 1
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar.bz2
License         : LGPL/GPL
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
export ac_cv_file__dev_random=yes
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} \
	--with-libgcrypt-prefix=${DEV_IMAGE}/%{_prefix} \
	--with-libtasn1-prefix=${DEV_IMAGE}/%{_prefix} NM=nm
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
