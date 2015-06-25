%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Abstraction layer for touchscreen panel events 
Name            : tslib
Version         : 1.0
Release         : 3
License         : LGPL
Vendor          : Freescale
Packager        : Ross Wille
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar.bz2
Patch1          : tslib-1.0-enable_input_events.patch
Patch2          : tslib-1.0-mx-pre_gen-2.patch
Patch3          : tslib-1.0-mx-pre_config.patch
Patch4          : tslib-1.0-glibc-2.7.x-open-O_CREAT-lack-parameter.patch
Patch5          : tslib-1.0-1394538963.patch
Patch6          : tslib-1.0-1417198155.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup
%patch1 -p1 
%patch2 -p1 
%patch3 -p1
if [ "${TC_TYPE}" = "UCLIBC" ] || [ "${TC_TYPE}" = "UCLIBC-SYSROOT" ]; then
    LIBC_FILE_NAME="`readlink \`${TOOLCHAIN_PREFIX}gcc ${TOOLCHAIN_CFLAGS} -print-file-name=libc.so.0\``"
else
    LIBC_FILE_NAME="`readlink \`${TOOLCHAIN_PREFIX}gcc ${TOOLCHAIN_CFLAGS} -print-file-name=libc.so.6\``"
fi

LIBC_VERSION=`echo "${LIBC_FILE_NAME}" | cut -d '-' -f 2`
if [ `echo ${LIBC_VERSION} | cut -d '.' -f 1` -eq 2 -a `echo ${LIBC_VERSION} | cut -d '.' -f 2` -ge 7 ]; then
%patch4 -p1
fi

touch aclocal.m4
sleep 1
find . -name Makefile.in | xargs touch
sleep 1
touch configure
%patch5 -p1
%patch6 -p1

%Build
#sed -i s/AS_HELP_STRING/AC_HELP_STRING/ configure.ac
#./autogen.sh
chmod +x ./configure
export ac_cv_func_malloc_0_nonnull=yes
./configure CC=${TOOLCHAIN_PREFIX}gcc --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make

%Install
#rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
rm -f $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/*.la
rm -f $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/ts/*.la
# Remove unused platform binaries
for so in arctic2.so collie.so corgi.so h3600.so mk712.so; do
	rm -f $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/usr/lib/ts/$so
done

%Clean
#rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
