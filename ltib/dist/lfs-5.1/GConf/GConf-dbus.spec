%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : The Gnome Config System using D-Bus for IPC
Name            : GConf-dbus
Version         : 2.16.0
Release         : 1
Vendor          : Freescale
Packager        : Rob Herring
Group           : System Environment/Base
Source          : %{name}-%{version}.tar.bz2
License         : LGPL
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --disable-gtk-doc
perl -pi -e 's,^sys_lib_search_path_spec=.*,sys_lib_search_path_spec=,' libtool
perl -pi -e 's,^sys_lib_dlsearch_path_spec=.*,sys_lib_dlsearch_path_spec=,' libtool
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
