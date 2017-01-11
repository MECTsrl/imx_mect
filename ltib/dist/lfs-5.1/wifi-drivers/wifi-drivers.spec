%define pfx /opt/freescale/rootfs/%{_target_cpu}
%define pkg_src  compat-drivers
%define pkg_rc   rc4
%define pkg_bld  su

Summary         : Wi-Fi drivers ported from newer kernels.
Name            : wifi-drivers
Version         : 3.9
Release         : 2
License         : GPL
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Kernel
URL             : https://www.kernel.org/pub/linux/kernel/projects/backports/stable/v%{version}-%{pkg_rc}/%{pkg_src}-%{version}-%{release}-%{pkg_bld}.tar.xz
Source1         : firmware-realtek_20160110-1_all.deb
Source2         : htc_9271.fw
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package common-rfs
Summary         : Common run time files for backported drivers.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Kernel
AutoReqProv     : no

%Description common-rfs
%name} package contents trimmed to just the common files that
are needed at run time on the target by the backported driver.

%Package ath9k_htc-rfs
Summary         : Run time files for the ath9k_htc driver.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Kernel
Requires        : %{name}-common-rfs
AutoReqProv     : no

%Description ath9k_htc-rfs
%name} package contents trimmed to just the files that are
needed at run time on the target for the ath9k_htc driver.

%Package rtlwifi-rfs
Summary         : Run time files for the rtlwifi driver.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Kernel
Requires        : %{name}-common-rfs
AutoReqProv     : no

%Description rtlwifi-rfs
%name} package contents trimmed to just the files that are
needed at run time on the target for the rtlwifi driver.


%Description
%{name} provides drivers released on newer kernels
backported for usage on older kernels.


#################################################################
%Prep
export LC_ALL
LC_ALL=C

%setup -T -c -n %{name}
cd ..; rmdir %{name}; ln -s ../../../projects/%{name} %{name}


#################################################################
%Build
export LC_ALL
LC_ALL=C

# Build the rtlwifi driver.
cd %{pkg_src}-%{version}-%{pkg_rc}-%{release}-%{pkg_bld}

./scripts/driver-select rtlwifi
make -j$(nproc) \
	prefix=%{_prefix} \
	CROSS_COMPILE=${TOOLCHAIN_PATH}/bin/${TOOLCHAIN_PREFIX} \
	ARCH=$LINTARCH \
	KLIB=${RPM_BUILD_ROOT}%{pfx} \
	KLIB_BUILD=${TOP}/rpm/BUILD/linux
./scripts/driver-select restore

./scripts/driver-select ath9k_htc
make -j$(nproc) \
	prefix=%{_prefix} \
	CROSS_COMPILE=${TOOLCHAIN_PATH}/bin/${TOOLCHAIN_PREFIX} \
	ARCH=$LINTARCH \
	KLIB=${RPM_BUILD_ROOT}%{pfx} \
	KLIB_BUILD=${TOP}/rpm/BUILD/linux
./scripts/driver-select restore


#################################################################
%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

mkdir -p $RPM_BUILD_ROOT%{pfx}/usr/sbin

# Firmware for rtlwifi driver
cd $RPM_BUILD_ROOT%{pfx}
ar -p %{SOURCE1} data.tar.xz | tar xJvf - $( ar -p %{SOURCE1} data.tar.xz | tar tJf - | grep 8192cu )
cd -

# Firmware for ath9k_htc driver
install -D -m 644 %{SOURCE2} $RPM_BUILD_ROOT%{pfx}/lib/firmware/$(basename %{SOURCE2})

cd %{pkg_src}-%{version}-%{pkg_rc}-%{release}-%{pkg_bld}

./scripts/driver-select rtlwifi
make -j$(nproc) install \
	DESTDIR=$RPM_BUILD_ROOT%{pfx} \
	prefix=%{_prefix} \
	CROSS_COMPILE=${TOOLCHAIN_PATH}/bin/${TOOLCHAIN_PREFIX} \
	ARCH=$LINTARCH \
	KLIB=${RPM_BUILD_ROOT}%{pfx} \
	KLIB_BUILD=${TOP}/rpm/BUILD/linux
./scripts/driver-select restore

./scripts/driver-select ath9k_htc
make -j$(nproc) install \
	DESTDIR=$RPM_BUILD_ROOT%{pfx} \
	prefix=%{_prefix} \
	CROSS_COMPILE=${TOOLCHAIN_PATH}/bin/${TOOLCHAIN_PREFIX} \
	ARCH=$LINTARCH \
	KLIB=${RPM_BUILD_ROOT}%{pfx} \
	KLIB_BUILD=${TOP}/rpm/BUILD/linux
./scripts/driver-select restore


#################################################################
%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


#################################################################
%Files
%defattr(-,root,root)
%{pfx}/*

%Files common-rfs
%defattr(-,root,root)
%{pfx}/lib/modules/2.6.35.3/updates/compat/compat.ko
%{pfx}/lib/modules/2.6.35.3/updates/compat/sch_codel.ko
%{pfx}/lib/modules/2.6.35.3/updates/compat/sch_fq_codel.ko
%{pfx}/lib/modules/2.6.35.3/updates/net/mac80211/mac80211.ko
%{pfx}/lib/modules/2.6.35.3/updates/net/wireless/cfg80211.ko

%Files rtlwifi-rfs
%defattr(-,root,root)
%{pfx}/lib/firmware/rtlwifi/rtl8192cufw.bin
%{pfx}/lib/modules/2.6.35.3/updates/drivers/net/wireless/rtlwifi/rtl8192c/rtl8192c-common.ko
%{pfx}/lib/modules/2.6.35.3/updates/drivers/net/wireless/rtlwifi/rtl8192cu/rtl8192cu.ko
%{pfx}/lib/modules/2.6.35.3/updates/drivers/net/wireless/rtlwifi/rtlwifi.ko

%Files ath9k_htc-rfs
%defattr(-,root,root)
%{pfx}/lib/firmware/htc_9271.fw
%{pfx}/lib/modules/2.6.35.3/updates/drivers/net/wireless/ath/ath.ko
%{pfx}/lib/modules/2.6.35.3/updates/drivers/net/wireless/ath/ath9k/ath9k.ko
%{pfx}/lib/modules/2.6.35.3/updates/drivers/net/wireless/ath/ath9k/ath9k_common.ko
%{pfx}/lib/modules/2.6.35.3/updates/drivers/net/wireless/ath/ath9k/ath9k_htc.ko
%{pfx}/lib/modules/2.6.35.3/updates/drivers/net/wireless/ath/ath9k/ath9k_hw.ko
