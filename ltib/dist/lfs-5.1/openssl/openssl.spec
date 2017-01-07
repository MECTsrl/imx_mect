%define base %(echo %{_prefix} | sed -e s,/usr.*$,,)
%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Secure Sockets Layer toolkit
Name            : openssl
Version         : 1.0.1s
Release         : 1
License         : BSD style
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : System Environment/Libraries
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed %{name} for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
AutoReqProv     : no

%Description rfs
%{name} package contents limited to just the files
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

case $ENDIAN in
    big)
        XTRA_OPTS="-DB_ENDIAN"
        ;;
    little)
        XTRA_OPTS="-DL_ENDIAN"
        ;;
    *)
        echo "Please set the ENDIAN environment variable to big|little"
        ;;
esac
case "$LINTARCH" in
    arm|m68k*)
       OSSL_ARCH="linux-generic32"
       ;;
    powerpc*)
       OSSL_ARCH="linux-ppc"
       ;;
    *)
       OSSL_ARCH="linux-$LINTARCH"
       ;;
esac

export TARGETMACH
export TARGETMACH=$CFGHOST
export BUILDMACH
export BUILDMACH=%{_build}

./Configure $OSSL_ARCH --prefix=%{_prefix} shared no-asm $XTRA_OPTS
make -j$(nproc)


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

make INSTALL_PREFIX=$RPM_BUILD_ROOT/%{pfx} install_sw


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/lib/engines/lib4758cca.so
%{pfx}/usr/lib/engines/libaep.so
%{pfx}/usr/lib/engines/libatalla.so
%{pfx}/usr/lib/engines/libcapi.so
%{pfx}/usr/lib/engines/libchil.so
%{pfx}/usr/lib/engines/libcswift.so
%{pfx}/usr/lib/engines/libgmp.so
%{pfx}/usr/lib/engines/libgost.so
%{pfx}/usr/lib/engines/libnuron.so
%{pfx}/usr/lib/engines/libpadlock.so
%{pfx}/usr/lib/engines/libsureware.so
%{pfx}/usr/lib/engines/libubsec.so
%{pfx}/usr/lib/libcrypto.so
%{pfx}/usr/lib/libcrypto.so.1.0.0
%{pfx}/usr/lib/libssl.so
%{pfx}/usr/lib/libssl.so.1.0.0
%{pfx}/usr/ssl/certs
%{pfx}/usr/ssl/openssl.cnf
%{pfx}/usr/ssl/private
