%define pfx /opt/freescale/rootfs/%{_target_cpu}
%define aname openssh
%define avers 4.3p2

Summary         : sftp-server using SSH protocol versions 1 and 2
Name            : sftp-server
Version         : %{avers}
Release         : 1
License         : BSD
Vendor          : Avid Technology
Packager        : Fritz Mueller
Group           : Applications/Internet
Source          : %{aname}-%{avers}.tar.gz
Source1         : openssl-0.9.8g.tar.gz
Patch0          : openssl-md4_size_t.patch
Patch1          : openssl-md5_size_t.patch
Patch2          : openssl-sha_size_t.patch
Patch3          : openssl-0.9.8g-lib64.patch
Patch4          : openssl-0.9.8g-ripemd_size_t.patch
Patch5          : openssl-0.9.8g-sec.patch
Patch6          : openssl-0.9.8g-cryptodev.patch
Patch7          : openssh-4.3p2-static-sftp-server.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed sftp-server for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/Internet
AutoReqProv     : no

%Description rfs
sftp-server package contents restricted to just the files that
are needed at run time on the target.


%Description
%{summary}

%Prep
export LC_ALL
LC_ALL=C

%setup -T -c
%setup -T -D -a 0
%setup -T -D -a 1
%patch7 -p1
cd openssl-0.9.8g
%patch0 -p1
%patch1 -p1
%patch2 -p1
%patch3 -p1
%patch4 -p1
%patch5 -p1
%patch6 -p1


%Build
export LC_ALL
LC_ALL=C

cd $RPM_BUILD_DIR/$RPM_PACKAGE_NAME-$RPM_PACKAGE_VERSION/openssl-0.9.8g
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
./Configure $OSSL_ARCH --prefix=%{_prefix} shared no-asm $XTRA_OPTS --with-cryptodev 
make -j$(nproc) build_crypto

cd $RPM_BUILD_DIR/$RPM_PACKAGE_NAME-$RPM_PACKAGE_VERSION/openssh-4.3p2
# Timestamp order is important.
for f in configure.ac configure.in aclocal.m4 configure config.h.in Makefile.am Makefile.in; do
	find . -name $f -exec touch {} \;
done
LD=gcc ./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} --with-zlib=$DEV_IMAGE/usr --with-ssl-dir=$RPM_BUILD_DIR/$RPM_PACKAGE_NAME-$RPM_PACKAGE_VERSION/openssl-0.9.8g --with-ldflags="-L$RPM_BUILD_DIR/$RPM_PACKAGE_NAME-$RPM_PACKAGE_VERSION/openssl-0.9.8g" --config-cache
make -j$(nproc) sysconfdir=%{_sysconfdir}/ssh sftp-server

%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

cd $RPM_BUILD_DIR/$RPM_PACKAGE_NAME-$RPM_PACKAGE_VERSION/openssh-4.3p2
make -j1 install-sftp-server sysconfdir=%{_sysconfdir}/ssh DESTDIR=$RPM_BUILD_ROOT/%{pfx}
cd -


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/libexec/sftp-server
