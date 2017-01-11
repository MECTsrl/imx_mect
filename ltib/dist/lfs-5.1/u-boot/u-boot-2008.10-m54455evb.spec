%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Universal Bootloader firmware
Name            : u-boot
Version         : 2008.10
Release         : 20081018
License         : GPL
Vendor          : Freescale
Packager        : Kurt Mahan
Group           : Applications/System
Source          : u-boot-%{version}.final.tar.bz2
Patch1		: u-boot-2008.10-5445x-dcache.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

Open source u-boot v2008.10 for M54455EVB

%Prep
%setup -n u-boot-%{version}
%patch1 -p1

%Build
echo Building UBOOT
make CROSS_COMPILE=$TOOLCHAIN_PREFIX distclean
make HOSTCC="$BUILDCC" CROSS_COMPILE=$TOOLCHAIN_PREFIX $PKG_U_BOOT_CONFIG_TYPE
make HOSTCC="$BUILDCC" HOSTSTRIP="$BUILDSTRIP" CROSS_COMPILE=$TOOLCHAIN_PREFIX

%Install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}/boot
for i in u-boot.bin u-boot u-boot.srec
do
    cp $i $RPM_BUILD_ROOT/%{pfx}/boot
done

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
