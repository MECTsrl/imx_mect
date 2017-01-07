%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : LZO is a portable lossless data compression library written in ANSI C.
Name            : lzo
Version         : 2.03
Release         : 0
License         : GPL
Vendor          : Freescale
Packager        : Ross Wille
Group           : System Environment/Libraries
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed lzo for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
AutoReqProv     : no


%Description rfs
lzo package contents restricted to just the files that are
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
if [ "$GNUTARCH" = m68knommu ]
then
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} \
	--disable-asm --disable-shared
else
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} \
	--disable-asm --enable-shared
fi
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
%{pfx}/usr/lib/liblzo2.so
%{pfx}/usr/lib/liblzo2.so.2
%{pfx}/usr/lib/liblzo2.so.2.0.0
