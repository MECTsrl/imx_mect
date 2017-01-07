%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : A Modbus library
Name            : libmodbus
Version         : 3.0.6
Release         : 1
License         : LGPLv2+
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed %{name} for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no

%Description rfs
%{name} package contents restricted to just the files that
are needed at run time on the target.


%Description
%{summary}


%Prep
export LC_ALL
LC_ALL=C

%setup -T -c -n %{name}
cd ..; rmdir %{name}; ln -s ../../../projects/%{name} %{name}


%Build
export LC_ALL
LC_ALL=C

# Timestamp order is important.
for f in configure.ac configure.in aclocal.m4 configure config.h.in Makefile.am Makefile.in; do
	find . -name $f -exec touch {} \;
done
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/lib/libmodbus.so
%{pfx}/usr/lib/libmodbus.so.5
%{pfx}/usr/lib/libmodbus.so.5.0.5
