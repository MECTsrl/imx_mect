%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : File manager for the Gnome Desktop
Name            : nautilus
Version         : 2.24.2
Release         : 1
License         : LGPL
Vendor          : Freescale
Packager        : Yu Miao
Group           : System Environment/Daemons
Source          : %{name}-%{version}.tar.bz2
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
export ORBIT_IDL=/usr/bin/orbit-idl-2
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} \
--with-x
make ORBIT_IDL=${ORBIT_IDL}

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
rm -f $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/*.la


%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*


