%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Performance Counters for Linux
Name            : perf
Version         : 3.0.35
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Terry Lv
Group           : Development/Tools
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
Performance counters are special hardware registers available on most modern
CPUs. These registers count the number of certain types of hw events: such
as instructions executed, cachemisses suffered, or branches mis-predicted -
without slowing down the kernel or applications. These registers can also
trigger interrupts when a threshold number of events have passed - and can
thus be used to profile the code that runs on that CPU.

The Linux Performance Counter subsystem provides an abstraction of these
hardware capabilities. It provides per task and per CPU counters, counter
groups, and it provides event capabilities on top of those.  It
provides "virtual" 64-bit counters, regardless of the width of the
underlying hardware counters.

%{summary}

%Prep

%Build
if [ -z "$PKG_KERNEL_KBUILD_PRECONFIG" ]
then
      KERNELDIR="$PWD/linux"
      KBUILD_OUTPUT="$PWD/linux"
else
      KERNELDIR="$PKG_KERNEL_PATH_PRECONFIG"
      KBUILD_OUTPUT="$(eval echo ${PKG_KERNEL_KBUILD_PRECONFIG})"
fi

# build the libraries and kernel modules 
cd ${KERNELDIR}/tools/perf
make CROSS_COMPILE=$TOOLCHAIN_PREFIX EXTRA_CFLAGS="-static -DGElf_Nhdr=Elf32_Nhdr"
cd -

%Install
rm -rf $RPM_BUILD_ROOT
if [ -z "$PKG_KERNEL_KBUILD_PRECONFIG" ]
then
      KERNELDIR="$PWD/linux"
      KBUILD_OUTPUT="$PWD/linux"
else
      KERNELDIR="$PKG_KERNEL_PATH_PRECONFIG"
      KBUILD_OUTPUT="$(eval echo ${PKG_KERNEL_KBUILD_PRECONFIG})"
fi
cd ${KERNELDIR}/tools/perf
PERF_INSTALL_DEST="$RPM_BUILD_ROOT/%{pfx}/usr"
mkdir -p $PERF_INSTALL_DEST
make install CROSS_COMPILE=$TOOLCHAIN_PREFIX EXTRA_CFLAGS="-static -DGElf_Nhdr=Elf32_Nhdr" DESTDIR=$PERF_INSTALL_DEST
cd -

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(755,root,root)
%{pfx}/*
