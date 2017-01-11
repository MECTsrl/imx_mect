%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : libiconv converts text from one encoding to another encoding.
Name            : libiconv
Version         : 1.11
Release         : 1
License         : LGPL
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : Development/Libraries
URL             : http://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.11.tar.gz
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup 

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
rm -f $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/*.la

cat << EOF > $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/include/iconv-detect.h
/* This is an auto-generated header, DO NOT EDIT! */

#define ICONV_ISO_D_FORMAT "iso-%d-%d"
#define ICONV_ISO_S_FORMAT "iso-%d-%s"
#define ICONV_10646 "iso-10646"
EOF

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
