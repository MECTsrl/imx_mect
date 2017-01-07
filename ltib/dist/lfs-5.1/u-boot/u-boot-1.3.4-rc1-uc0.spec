%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Universal Bootloader firmware
Name            : u-boot
Version         : 1.3.4
Release         : rc1
License         : GPL
Vendor          : Freescale
Packager        : Matt Waddel
Group           : Applications/System
Source          : u-boot-%{version}-rc1.tar.gz
Patch0          : u-boot-1.3.4-rc1-m5253demo.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

Open source u-boot v1.3.4-rc1

%Prep
%setup -n u-boot
%patch0 -p1

%Build
PKG_U_BOOT_CONFIG_TYPE=${SYSCFG_BOOT_CPU}
make distclean
make HOSTCC="$BUILDCC" CROSS_COMPILE=$TOOLCHAIN_PREFIX $PKG_U_BOOT_CONFIG_TYPE
make HOSTCC="$BUILDCC" HOSTSTRIP="$BUILDSTRIP" CROSS_COMPILE=$TOOLCHAIN_PREFIX

%Install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}/boot
for i in u-boot.bin u-boot
do
    cp $i $RPM_BUILD_ROOT/%{pfx}/boot
done

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
