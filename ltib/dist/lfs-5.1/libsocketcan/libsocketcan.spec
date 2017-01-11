%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Library to allow control of basic functions in socketcan from userspace
Name            : libsocketcan
Version         : 0.0.8
Release         : 0
License         : GNU LGPLv2.1
Vendor          : Freescale
Packager        : Rogerio Pimentel
Group           : System Environment/Libraries
URL             : http://www.pengutronix.de/software/libsocketcan/download/
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed libsocketcan for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
AutoReqProv     : no

%Description rfs
libsocketcan package contents restricted to just the files
that are needed at run time on the target.


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
%{pfx}/usr/lib/libsocketcan.so
%{pfx}/usr/lib/libsocketcan.so.2
%{pfx}/usr/lib/libsocketcan.so.2.2.0
