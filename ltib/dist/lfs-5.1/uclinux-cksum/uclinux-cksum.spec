%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Utility to generate the checksum & count the bytes in a file
Name            : cksum
Version         : 19990607
Release         : 1
License         : BSD
Vendor          : Freescale
Packager        : Steve Papacharalambous
Group           : System Environment/Base
Source          : %{name}-%{version}.tar.gz
Patch1          : cksum-19990607-1122994071.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

This particular version of cksum is required by the uClinux host tools
to build the final target image.


%Prep
%setup 
%patch1 -p1

%Build
make

%Install
rm -rf ${RPM_BUILD_ROOT}
mkdir -p ${RPM_BUILD_ROOT}/%{pfx}/%{_prefix}/usr/bin

# Change the name of the executable to us-cksum to avoid possible confusion
# with existing host distribution cksum.
install ${RPM_BUILD_DIR}/%{name}-%{version}/cksum ${RPM_BUILD_ROOT}/%{pfx}/%{_prefix}/usr/bin/uc-cksum


%Clean
rm -rf ${RPM_BUILD_ROOT}

%Files
%defattr(-,root,root)
%{pfx}/*
