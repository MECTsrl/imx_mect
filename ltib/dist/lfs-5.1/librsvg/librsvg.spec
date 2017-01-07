%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Renderer library for SVG files
Name            : librsvg
Version         : 2.22.3
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
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} \
--with-x
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


