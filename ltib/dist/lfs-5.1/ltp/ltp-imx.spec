%define pfx /opt/freescale/rootfs/%{_target_cpu}
%define vte_version 111100

Summary         : verification test environment for imx platforms.
Name            : ltp-imx
Version         : 20090930
Release         : 7
License         : GPL
Vendor          : Freescale
Packager        : Hake Huang
Group           : TEST
URL             : http://sourceforge.net/projects/ltp/files/LTP%20Source/_OLD_ltp-20090630/ltp-full-20090930.tgz/download
Source          : ltp-full-%{version}.tgz
Source1         : vte_test_stream_4.5.tar.gz
Source2         : %{name}_0001_vte_source_111101.tar.gz
Source3         : %{name}_0002_vte_test_data_%{vte_version}.tar.gz
Source4         : %{name}_0003_add_top_makefile_%{vte_version}.tar.gz
Source5         : %{name}_0004_add_armconfig_111101.tar.gz
Source6         : %{name}_0005_add_mx6q_config_%{vte_version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup -n ltp-full-%{version} -a1 -a2 -a3 -a4 -a5 -a6


%Build

if [ -z "$PKG_KERNEL_KBUILD_PRECONFIG" ]
then
      KERNELDIR="$PWD/../linux"
      KBUILD_OUTPUT="$PWD/../linux"
else
      KERNELDIR="$PKG_KERNEL_PATH_PRECONFIG"
      KBUILD_OUTPUT="$(eval echo ${PKG_KERNEL_KBUILD_PRECONFIG})"
fi
export KLINUX_SRCDIR=$KERNELDIR
export KLINUX_BLTDIR=$KBUILD_OUTPUT
export ARCH_CPU=arm
export ARCH_PLATFORM=$PLATFORM
export CFLAGS=$CFLAGS" -I${KLINUX_SRCDIR}/arch/arm/include -I${KLINUX_SRCDIR}/include"
sh armconfig
make vte -f Makefile_vte

%Install
rm -rf $RPM_BUILD_ROOT
install -d $RPM_BUILD_ROOT/%{pfx}/vte-%{vte_version}/pan/cgi
install -d $RPM_BUILD_ROOT/%{pfx}/vte-%{vte_version}/lib
install -d $RPM_BUILD_ROOT/%{pfx}/vte-%{vte_version}/runtest
install -d $RPM_BUILD_ROOT/%{pfx}/vte-%{vte_version}/testcases/bin

for i in ver_linux runltp runltplite.sh IDcheck.sh runalltests.sh; do
	install ${i} $RPM_BUILD_ROOT/%{pfx}/vte-%{vte_version}
done
for i in ltp-bump ltp-pan ltp-scanner; do
	install pan/${i} $RPM_BUILD_ROOT/%{pfx}/vte-%{vte_version}/pan/
done

install pan/cgi/* $RPM_BUILD_ROOT/%{pfx}/vte-%{vte_version}/pan/cgi/
install lib/libltp.a $RPM_BUILD_ROOT/%{pfx}/vte-%{vte_version}/lib/
install runtest/* $RPM_BUILD_ROOT/%{pfx}/vte-%{vte_version}/runtest/
install testcases/bin/* $RPM_BUILD_ROOT/%{pfx}/vte-%{vte_version}/testcases/bin/

#install test streams
install -d $RPM_BUILD_ROOT/%{pfx}/test_stream/alsa_stream
install alsa_stream/* $RPM_BUILD_ROOT/%{pfx}/test_stream/alsa_stream

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
