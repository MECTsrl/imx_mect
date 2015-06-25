%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : A file compression utility.
Name            : zip
Version         : 3.0.0
Release         : 0
License         : BSD
Vendor          : Mect srl
Packager        : Monica Donno
Group           : Applications/File
Source          : %{name}-%{version}.tar.bz2
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
make -f unix/Makefile generic_gcc


%Install
rm -rf $RPM_BUILD_ROOT
 make -f unix/Makefile install PREFIX=$RPM_BUILD_ROOT/%{pfx}/%{_prefix}
$TOOLCHAIN_PATH/bin/${TOOLCHAIN_PREFIX}strip --strip-unneeded $RPM_BUILD_ROOT/%{pfx}/usr/bin/zip

%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*


