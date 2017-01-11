%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : TrueType font rasterizer
Name            : freetype
Version         : 2.3.9
Release         : 1
License         : GPL or FTL
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : System Environment/Libraries
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed freetype for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
AutoReqProv     : no

%Description rfs
freetype package contents restricted to just the files that
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

export CC_BUILD="$BUILDCC"

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
make DESTDIR=$RPM_BUILD_ROOT/%{pfx} install


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/bin/freetype-config
%{pfx}/usr/lib/libfreetype.so
%{pfx}/usr/lib/libfreetype.so.6
%{pfx}/usr/lib/libfreetype.so.6.3.20
%{pfx}/usr/share/aclocal/freetype2.m4
