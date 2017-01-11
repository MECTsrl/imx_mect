%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : GLib bindings for D-BusGLib bindings for D-Bus
Name            : dbus-glib
Version         : 0.76
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Rob Herring
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar.gz
Patch1          : dbus-glib-0.76-build-only-core-components.patch
Patch2          : dbus-glib-0.76-pregen-introspect-xml.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup
%patch1 -p1
%patch2 -p0

%Build
export ac_cv_func_posix_getpwnam_r=yes
export ac_cv_have_abstract_sockets=yes
export DBUS_DAEMONDIR=/bin
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} --with-introspect-xml=dbus-bus-introspect.xml
make
#make -B -C dbus CC="${BUILDCC}" dbus-binding-tool

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
rm -f $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/*.la

%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*


