%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : ATCM control runtime system application
Name            : 4c_runtime
Version         : 0.0
Release         : 1
License         : GPL
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/File
URL             : http://www.mect.it/
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}/local
AutoReqProv     : no


%Package lfs
Summary         : Trimmed %{name} to just the run-times needed in the root file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/File
AutoReqProv     : no

%description lfs
%{name} package contents limited to just the run-times needed
on the target.


%description
ATCM control runtime system provides the run-time execution
environment for the PLC applications built using the ATCM
control engineering SDK.

%prep
export LC_ALL
LC_ALL=C

%setup -T -c -n %{name}

# Sources not available
if test -d ../../../../projects/%{name}; then
	cd ..; rmdir %{name}; ln -s ../../../projects/%{name} %{name}
fi


%build
export LC_ALL
LC_ALL=C

export MECT_RFSDIR
MECT_RFSDIR=$DEV_IMAGE
export MECT_CSXCDIR
MECT_CSXCDIR=$TOOLCHAIN_PATH
export MECT_CC_DIRECTORY
MECT_CC_DIRECTORY=$TOOLCHAIN_PATH
export MECT_CC_VERSION
MECT_CC_VERSION= 
export MECT_CC_RADIX
MECT_CC_RADIX=$CFGHOST

# Nothing to build
test -r _fcrts.mak || exit 0

make -j1 -f _fcrts.mak TARGET=4CPC DEBUG=0 PRODUCT="USE_CROSSTABLE" MECT_ROOTFS=$MECT_RFSDIR MECT_CC_VERSION=$MECT_CC_VERSION MECT_CC_DIRECTORY=$MECT_CC_DIRECTORY MECT_CC_RADIX=$MECT_CC_RADIX clobber
make -j1 -f _fcrts.mak TARGET=4CPC DEBUG=0 PRODUCT="USE_CROSSTABLE" MECT_ROOTFS=$MECT_RFSDIR MECT_CC_VERSION=$MECT_CC_VERSION MECT_CC_DIRECTORY=$MECT_CC_DIRECTORY MECT_CC_RADIX=$MECT_CC_RADIX all


%install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

mkdir -p $RPM_BUILD_ROOT/%{pfx}/local

if ! test -r bin/fcrts; then
	# Target was not build, create dummy placeholder.
	install -D -m 0644 /dev/null $RPM_BUILD_ROOT/%{pfx}/local/root/fcrts
else
	# Install the real thing.
	install -D -m 0755 bin/fcrts $RPM_BUILD_ROOT/%{pfx}/local/root/fcrts
fi


%clean
sudo rm -rf $RPM_BUILD_ROOT


%files
%defattr(-,root,root)
%{pfx}/local/root/fcrts

%files lfs
%defattr(-,root,root)
%{pfx}/local/root/fcrts
