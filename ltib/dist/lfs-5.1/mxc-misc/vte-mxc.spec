%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : vte test suite for mxc platforms.
Name            : vte-mxc
Version         : 3.4pre
Release         : 1
License         : xxxx
Vendor          : Freescale
Packager        : Alan Tull
Group           : TEST
Source          : vte-%{version}.tgz
#patch0		: vte-%{version}-1.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup -n vte-%{version}
#%patch0 -p1

mv tools/Toulouse\ environment/ tools/Toulouse_environment
chmod 755 $(find . -name Makefile)

if [ -z "$PKG_KERNEL_KBUILD_PRECONFIG" ]
then
      KERNELDIR="$PWD/../linux"
      KBUILD_OUTPUT="$PWD/../linux"
else
      KERNELDIR="$PKG_KERNEL_PATH_PRECONFIG"
      KBUILD_OUTPUT="$(eval echo ${PKG_KERNEL_KBUILD_PRECONFIG})"
fi

perl -pi -e 's,.*CROSS_COMPILER=.*$,   CROSS_COMPILER=,' Makefile
perl -pi -e "s,export KLINUX_SRCDIR=.*$,export KLINUX_SRCDIR=$KERNELDIR," Makefile
perl -pi -e "s,export KLINUX_BLTDIR=.*$,export KLINUX_BLTDIR=$KBUILD_OUTPUT," Makefile
perl -pi -e "s,export ARCH_PLATFORM=.*$,export ARCH_PLATFORM=$PLATFORM," Makefile

%Build
make vte

#build ltp:
cd testcases
rm -rf gtk_tests_suite DOTS mm_tests_suite open* pounder21 qt_tests_suite
cd ..
# Don't do make install
sed -r -i 's,\@\$\(MAKE\) -C testcases\/.* install,# @$(MAKE) -C testcases/qt_tests_suite install,g' Makefile
#grep -lIr '/usr/bin/expect' *|xargs rm -f
#make ltp

%Install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}/vte-%{version}/pan/cgi
mkdir -p $RPM_BUILD_ROOT/%{pfx}/vte-%{version}/lib
mkdir -p $RPM_BUILD_ROOT/%{pfx}/vte-%{version}/runtest
mkdir -p $RPM_BUILD_ROOT/%{pfx}/vte-%{version}/testcases/bin

for i in ver_linux runltp runltplite.sh IDcheck.sh runalltests.sh; do
	cp -f ${i} $RPM_BUILD_ROOT/%{pfx}/vte-%{version}
done
for i in bump pan scanner; do
	cp -f pan/${i} $RPM_BUILD_ROOT/%{pfx}/vte-%{version}/pan/
done

cp -f pan/cgi/* $RPM_BUILD_ROOT/%{pfx}/vte-%{version}/pan/cgi/
cp -f lib/libltp.a $RPM_BUILD_ROOT/%{pfx}/vte-%{version}/lib/
cp -f runtest/* $RPM_BUILD_ROOT/%{pfx}/vte-%{version}/runtest/
cp -rf testcases/bin/* $RPM_BUILD_ROOT/%{pfx}/vte-%{version}/testcases/bin/

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
