%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : D-Bus message bus
Name            : dbus
Version         : 1.2.3
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Rob Herring
Group           : System Environment/Daemons
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
export ac_cv_have_abstract_sockets=yes
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} \
 --enable-abstract-sockets --disable-xml-docs --disable-doxygen-docs
perl -pi -e 's,^sys_lib_search_path_spec=.*,sys_lib_search_path_spec=,' libtool
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


