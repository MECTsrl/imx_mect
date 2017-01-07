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
Patch1		: u-boot-2008.10-54451-revd-2.patch
Patch2		: u-boot-2008.10-5445x-dcache.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

Open source u-boot v2008.10 for M54451EVB

%Prep
%setup -n u-boot-%{version}
%patch1 -p1
%patch2 -p1

%Build
echo Building Parallel UBOOT
make CROSS_COMPILE=$TOOLCHAIN_PREFIX distclean
make HOSTCC="$BUILDCC" CROSS_COMPILE=$TOOLCHAIN_PREFIX M54451EVB_config
make HOSTCC="$BUILDCC" HOSTSTRIP="$BUILDSTRIP" CROSS_COMPILE=$TOOLCHAIN_PREFIX
mv u-boot u-boot-parallel.save
mv u-boot.bin u-boot-parallel.bin.save
mv u-boot.srec u-boot-parallel.srec.save
echo Building Serial UBOOT
make CROSS_COMPILE=$TOOLCHAIN_PREFIX distclean
make HOSTCC="$BUILDCC" CROSS_COMPILE=$TOOLCHAIN_PREFIX M54451EVB_stmicro_config
make HOSTCC="$BUILDCC" HOSTSTRIP="$BUILDSTRIP" CROSS_COMPILE=$TOOLCHAIN_PREFIX
mv u-boot u-boot-serial.save
mv u-boot.bin u-boot-serial.bin.save
mv u-boot.srec u-boot-serial.srec.save

%Install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}/boot
cp u-boot-parallel.save $RPM_BUILD_ROOT/%{pfx}/boot/u-boot-parallel
cp u-boot-parallel.bin.save $RPM_BUILD_ROOT/%{pfx}/boot/u-boot-parallel.bin
cp u-boot-parallel.srec.save $RPM_BUILD_ROOT/%{pfx}/boot/u-boot-parallel.srec
cp u-boot-serial.save $RPM_BUILD_ROOT/%{pfx}/boot/u-boot-serial
cp u-boot-serial.bin.save $RPM_BUILD_ROOT/%{pfx}/boot/u-boot-serial.bin
cp u-boot-serial.srec.save $RPM_BUILD_ROOT/%{pfx}/boot/u-boot-serial.srec

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
