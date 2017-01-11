%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Evolution Data Server
Name            : evolution-data-server
Version         : 2.24.0
Release         : 1
License         : LGPL
Vendor          : Freescale
Packager        : Rob Herring
Group           : System Environment/Daemons
Source          : %{name}-%{version}.tar.bz2
Patch1          : evolution-data-server-2.24.0-configure-cross-compile-fix.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup
%patch1 -p0

%Build
export ac_cv_have_abstract_sockets=yes
export ac_cv_libiconv_utf8=yes
export ORBIT_IDL=/usr/bin/orbit-idl-2
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} --disable-glibtest
make ORBIT_IDL=${ORBIT_IDL}

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
find $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/ -name "*.la" | xargs rm -f

%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*


