%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : A high-performance CORBA Object Request Broker
Name            : ORBit2
Version         : 2.14.16
Release         : 1
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : Development/Tools
Source          : %{name}-%{version}.tar.bz2
License         : LGPL/GPL
Patch1          : ORBit2-2.14.16-configure-cross-compile-fix.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup
%patch1 -p1

%Build
export ac_cv_c_bigendian=no
export ac_cv_alignof_CORBA_octet=1
export ac_cv_alignof_CORBA_boolean=1
export ac_cv_alignof_CORBA_char=1
export ac_cv_alignof_CORBA_wchar=2
export ac_cv_alignof_CORBA_short=2
export ac_cv_alignof_CORBA_long=4
export ac_cv_alignof_CORBA_struct=4
export ac_cv_alignof_CORBA_pointer=4
export ac_cv_alignof_CORBA_float=4
export ac_cv_alignof_CORBA_double=8
export ac_cv_alignof_CORBA_long_double=8
export ac_cv_alignof_CORBA_long_long=8
export IDL_COMPILER=/usr/bin/orbit-idl-2
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make IDL_COMPILER=/usr/bin/orbit-idl-2


%Install
rm -rf $RPM_BUILD_ROOT
export IDL_COMPILER=/usr/bin/orbit-idl-2
make install IDL_COMPILER=/usr/bin/orbit-idl-2 DESTDIR=$RPM_BUILD_ROOT/%{pfx}
rm -f $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/*.la

%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*
