%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Universal Bootloader firmware
Name            : u-boot
Version         : 1.3.0
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Joe D'Abbraccio
Group           : Applications/System
Source          : %{name}-%{version}-rc2-6c9b54a1.tgz
Patch1          : %{name}-%{version}-rc2-SPCR_TSEC-fix.patch
Patch2          : %{name}-%{version}-rc2-add-RTL821x-PHY.patch
Patch3          : %{name}-%{version}-rc2-add-MPC837xE-RDB.patch
Patch4          : %{name}-%{version}-rc2-MPC8379E-RDB-sys-perf-tweaks.patch
Patch5          : %{name}-1.2.0-mpc837xerdb-vsc7385-load.patch
Patch6          : %{name}-%{version}-rc2-MPC837xE-RDB-enable-NAND.patch
Patch7          : %{name}-%{version}-rc2-MPC837xE-RDB-add-PCI-express.patch
Patch8          : %{name}-%{version}-rc2-MPC837xE-RDB-Corrected-references.patch
Patch9          : %{name}-%{version}-mpc837xerdb-hrcw-sata-fix.patch
Patch10         : %{name}-%{version}-mpc83xx-rodata-str-1.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

All source and patches from Freescale.

%Prep
%setup -n u-boot-mpc83xx
%patch1 -p1
%patch2 -p1
%patch3 -p1
%patch4 -p1
%patch5 -p1
%patch6 -p1
%patch7 -p1
%patch8 -p1
%patch9 -p1
%patch10 -p1

%Build
PKG_U_BOOT_CONFIG_TYPE=${PKG_U_BOOT_CONFIG_TYPE:-MPC8349ADS_config}
make HOSTCC="$BUILDCC" CROSS_COMPILE=$TOOLCHAIN_PREFIX $PKG_U_BOOT_CONFIG_TYPE
make HOSTCC="$BUILDCC" HOSTSTRIP="$BUILDSTRIP" \
     CROSS_COMPILE=$TOOLCHAIN_PREFIX $PKG_U_BOOT_BUILD_ARGS all

%Install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}/boot
for i in u-boot.bin u-boot examples/vsc7385_load/vsc7385_load.bin
do
    cp $i $RPM_BUILD_ROOT/%{pfx}/boot
done

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
