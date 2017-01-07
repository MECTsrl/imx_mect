%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : zlib compression utilities and libraries
Name            : zlib
Version         : 1.2.3
Release         : 2
License         : zlib (Distributable)
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : Development/Libraries
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed zlib for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Development/Libraries
AutoReqProv     : no

%Description rfs
zlib package contents restricted to just the files that are
needed at run time on the target.


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
./configure --prefix=%{_prefix} --shared
mv Makefile Makefile.shared
./configure --prefix=%{_prefix}
mv Makefile Makefile.static
make -f Makefile.shared
make -f Makefile.static


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT%{pfx}%{_prefix}
make -f Makefile.shared install prefix=${RPM_BUILD_ROOT}%{pfx}%{_prefix}
make -f Makefile.static install prefix=${RPM_BUILD_ROOT}%{pfx}%{_prefix}


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/lib/libz.so
%{pfx}/usr/lib/libz.so.1
%{pfx}/usr/lib/libz.so.1.2.3
