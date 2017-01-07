%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Take photos and videos using webcam
Name            : cheese
Version         : 2.24.2
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Yu Miao
Group           : System Environment/Daemons
Source          : %{name}-%{version}.tar.gz
Patch1          : %{name}-%{version}-cross-compile-fixes.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup
%patch1 -p1

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
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


