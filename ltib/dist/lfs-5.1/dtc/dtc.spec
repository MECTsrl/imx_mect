%define pfx /opt/freescale/rootfs/%{_target_cpu}

# Note, please leave version in this format to make sure
# rpm does the right update thing for the host package
#
Summary         : The Device Tree Compiler for Flat Device Trees
Name            : dtc
Version         : 1.2.0
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Ebony Zhu / Stuart Hughes
Group           : Development/Tools
Source          : %{name}-1.2.0.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

from http://www.jdl.com/gitweb
made with: 
git-archive --format=tar --prefix=dtc-1.2.0/ v1.2.0 | gzip > dtc-1.2.0.tar.gz

Tag Version v1.2.0
sha1: 52c356d81b1b5b5426f53655e782c37793c3637e

%Prep
%setup -n %{name}-1.2.0

%Build
make

%Install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/bin
make install PREFIX=%{_prefix} DESTDIR=$RPM_BUILD_ROOT/%{pfx}
if [ -n "$PKG_DTC_NOT_WANT_EXE" ]
then
    rm -rf $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/bin
fi
if [ -z "$PKG_DTC_WANT_FDT" ]
then
    rm -rf $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/include
    rm -rf $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib
fi


%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
