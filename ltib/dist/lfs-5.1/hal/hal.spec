%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Hardware abstraction layer
Name            : hal
Version         : 0.5.10
Release         : 1
Vendor          : Freescale
Packager        : Yu Miao
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar.gz
Patch1          : %{name}-%{version}-cross-compile-fixes.patch
License         : GPL
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup
%patch1 -p1

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} \
--enable-verbose-mode --with-hal-user=haldaemon --with-hal-group=haldaemon \
--with-backend=linux --with-dbus-sys=/usr/etc/dbus-1/system.d/ \
--with-cpufreq=no --with-usb-csr=no \
--with-pci-ids=/usr/share/ --with-usb-ids=/usr/share/
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
