%define pfx /opt/freescale/rootfs/%{_target_cpu}
%define archname termcap

Summary         : A basic system library for accessing the termcap database.
Name            : libtermcap
Version         : 2.0.8
Release         : 31_1
License         : LGPL
Vendor          : Freescale Inc
Packager        : Steve Papacharalambous
Group           : System Environment/Libraries
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed libtermcap for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
AutoReqProv     : no

%Description rfs
libtermcap package contents restricted to just the files that
are needed at run time on the target.


%Description
The libtermcap package contains a basic system library needed to
access the termcap database.  The termcap library supports easy access
to the termcap database, so that programs can output character-based
displays in a terminal-independent manner.


%Prep
export LC_ALL
LC_ALL=C

%setup -T -c -n %{name}
cd ..; rmdir %{name}; ln -s ../../../projects/%{name} %{name}


%Build
export LC_ALL
LC_ALL=C

if [ "$GNUTARCH" = m68knommu ]
then
   MAKEOPTS="TARGETS=libtermcap.a"
fi
make $MAKEOPTS


%Install
export LC_ALL
LC_ALL=C

for i in usr/lib %{_infodir} usr/include etc lib
do
    mkdir -p ${RPM_BUILD_ROOT}/%{pfx}/$i
done

if [ "$GNUTARCH" = m68knommu ]
then
( cp libtermcap.a ${RPM_BUILD_ROOT}/%{pfx}/lib/
  cp termcap.h ${RPM_BUILD_ROOT}/%{pfx}%{_prefix}/include/
  cp termcap.info* ${RPM_BUILD_ROOT}/%{pfx}/%{_infodir}
  cd ${RPM_BUILD_ROOT}/%{pfx}
  cd ./%{_infodir}
  gzip -9nf ./termcap.info*
  chmod 644 ./termcap.info*
)

else
export PATH=/sbin:$PATH
make prefix=${RPM_BUILD_ROOT}/%{pfx}%{_prefix} install

install -c -m644 termcap.src ${RPM_BUILD_ROOT}/%{pfx}/etc/termcap
cp termcap.info* ${RPM_BUILD_ROOT}/%{pfx}/%{_infodir}

( cd ${RPM_BUILD_ROOT}/%{pfx}
  rm -f ./etc/termcap
  mv ./usr/lib/libtermcap.so* ./lib
  ln -sf libtermcap.so.%{version} ./lib/libtermcap.so.2
  ln -sf libtermcap.so.2 ./lib/libtermcap.so
  cd usr/lib
  ln -sf ../../lib/libtermcap.so.%{version} libtermcap.so
  cd ../..
  strip -R .comments --strip-unneeded ./lib/libtermcap.so.%{version}
  cd ./%{_infodir}
  gzip -9nf ./termcap.info*
  chmod 644 ./termcap.info*
)
fi


%Clean
export LC_ALL
LC_ALL=C

rm -rf ${RPM_BUILD_ROOT}
rm -rf ${RPM_BUILD_DIR}/%{archname}-%{version}


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/lib/libtermcap.so
%{pfx}/lib/libtermcap.so.2
%{pfx}/lib/libtermcap.so.2.0.8
%{pfx}/usr/lib/libtermcap.so
