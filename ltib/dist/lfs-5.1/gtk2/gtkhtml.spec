%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : HTML rendering/editing library
Name            : gtkhtml
Version         : 3.24.2
Release         : 2
License         : LGPL
Vendor          : Freescale
Packager        : Yu Miao
Group           : System Environment/Daemons
Source          : %{name}-%{version}.tar.bz2
Patch0          : gtkhtml-gnu-source.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup
%patch0 -p1

%Build
export PKG_CONFIG_PATH=${PKG_CONFIG_PATH}:${DEV_IMAGE}/usr/share/pkgconfig
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
find $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/ -name "*.la" | xargs rm -f


%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*


