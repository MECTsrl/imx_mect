%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Libraries, includes, etc. to develop XML/HTML applications
Name            : libxml2
Version         : 2.6.28
Release         : 2
Vendor          : Freescale
Packager        : Jason Jin/Stuart Hughes/Kurt Mahan
Group           : Development/Libraries
Source          : %{name}-%{version}.tar.gz
Patch0          : %{name}-2.6-glibc-2.7.x-open-O_CREAT-lack-parameter.patch
License         : MIT
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup 
if [ "${TC_TYPE}" = "UCLIBC" ] || [ "${TC_TYPE}" = "UCLIBC-SYSROOT" ]; then
    LIBC_FILE_NAME="`readlink \`${TOOLCHAIN_PREFIX}gcc ${TOOLCHAIN_CFLAGS} -print-file-name=libc.so.0\``"
else
    LIBC_FILE_NAME="`readlink \`${TOOLCHAIN_PREFIX}gcc ${TOOLCHAIN_CFLAGS} -print-file-name=libc.so.6\``"
fi

LIBC_VERSION=`echo "${LIBC_FILE_NAME}" | cut -d '-' -f 2`
if [ `echo ${LIBC_VERSION} | cut -d '.' -f 1` -eq 2 -a `echo ${LIBC_VERSION} | cut -d '.' -f 2` -ge 7 ]; then
%patch0 -p1
fi

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} --with-history --without-python
make

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
find $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/ -name "*.la" | xargs rm -f

%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*
