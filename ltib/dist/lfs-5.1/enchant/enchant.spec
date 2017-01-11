%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Wrapper library for various spell checker engines
Name            : enchant
Version         : 1.2.5
Release         : 1
License         : LGPL
Vendor          : Freescale
Packager        : Yu Miao
Group           : System Environment/Daemons
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
eval ac_cv_file__proc_self_maps=no \
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} \
--cache-file=config.cache
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


