%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Base Libraries (from toolchain).
Name            : base_libs
Version         : 1.2
Release         : 1
License         : LGPL
Vendor          : Freescale Inc.
Packager        : Steve Papacharalambous/Stuart Hughes
Group           : System Environment/Libraries
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed base_libs for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
AutoReqProv     : no

%Description rfs
base_libs package contents restricted to just the files that
are needed at run time on the target.


%Description
%{summary}


%Prep


%Build
export LC_ALL
LC_ALL=C

cat <<TXT
PKG_LIBC_WANT_SHARED_LIBS   : $PKG_LIBC_WANT_SHARED_LIBS
PKG_LIBC_WANT_CRT_FILES     : $PKG_LIBC_WANT_CRT_FILES
PKG_LIBC_WANT_HEADERS1      : $PKG_LIBC_WANT_HEADERS1
PKG_LIBC_WANT_STATIC_LIBS   : $PKG_LIBC_WANT_STATIC_LIBS
PKG_LIBC_WANT_C_LOCALES     : $PKG_LIBC_WANT_C_LOCALES
PKG_CXX_WANT_SHARED_LIBS    : $PKG_CXX_WANT_SHARED_LIBS
PKG_CXX_WANT_HEADERS        : $PKG_CXX_WANT_HEADERS
PKG_CXX_WANT_STATIC_LIBS    : $PKG_CXX_WANT_STATIC_LIBS
PKG_GCC_WANT_LIBGCC_SHARED  : $PKG_GCC_WANT_LIBGCC_SHARED
TXT


# For sysroot toolchains strip of the final "usr/bin/" from the path else
# strip "bin/"
set +e
${TOOLCHAIN_PREFIX}gcc -v 2>&1 | grep -q "prefix=/usr"
if test $? -ne 0
then
TC_PREFIX="`which ${TOOLCHAIN_PREFIX}gcc | perl -p -e 's,/bin/'${TOOLCHAIN_PREFIX}'gcc,,'`"
else
TC_PREFIX="`which ${TOOLCHAIN_PREFIX}gcc | perl -p -e 's,/usr/bin/'${TOOLCHAIN_PREFIX}'gcc,,'`"
fi
set -e


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
X_DIR=`echo $TOOLCHAIN_PREFIX | sed -e 's,-$,,'`


# For sysroot toolchains strip of the final "usr/bin/" from the path else
# strip "bin/"
set +e
${TOOLCHAIN_PREFIX}gcc -v 2>&1 | grep -q "prefix=/usr"
if test $? -ne 0
then
TC_PREFIX="`which ${TOOLCHAIN_PREFIX}gcc | perl -p -e 's,/bin/'${TOOLCHAIN_PREFIX}'gcc,,'`"
SYSROOT_TC="no"
else
TC_PREFIX="`which ${TOOLCHAIN_PREFIX}gcc | perl -p -e 's,/usr/bin/'${TOOLCHAIN_PREFIX}'gcc,,'`"
SYSROOT_TC="yes"
fi
set -e


if [ "$TOOLCHAIN_TYPE" = "64" ]
then
    SLIBS=lib64
else
    SLIBS=lib
fi

if [ -d "$TC_PREFIX/$X_DIR/libc" ]
then
    TC_TYPE=CSL
elif [ -d "$TC_PREFIX/$X_DIR/sysroot" ]
then
    TC_TYPE=EGLIBC
elif [ -d "$TC_PREFIX/$X_DIR/sys-root" ]
then
    TC_TYPE=XTOOL-SYSROOT
elif [ -d "$TC_PREFIX/$X_DIR/target_utils" ]
then
    if [ "${SYSROOT_TC}" = "yes" ]
    then
        TC_TYPE=UCLIBC-SYSROOT
    else
        TC_TYPE=UCLIBC
    fi
else
    TC_TYPE=XTOOL
fi

if [ "${TC_TYPE}" = "UCLIBC" ] || [ "${TC_TYPE}" = "UCLIBC-SYSROOT" ]
then
    SHARED_LIBS_DIR="`dirname \`${TOOLCHAIN_PREFIX}gcc ${TOOLCHAIN_CFLAGS} -print-file-name=libc.so.0\``"
else
    SHARED_LIBS_DIR="`dirname \`${TOOLCHAIN_PREFIX}gcc ${TOOLCHAIN_CFLAGS} -print-file-name=libc.so.6\``"
fi

STATIC_LIBS_DIR="`dirname \`${TOOLCHAIN_PREFIX}gcc ${TOOLCHAIN_CFLAGS} -print-file-name=libc.a\``"
GCC_SLIB_DIR="`dirname \`${TOOLCHAIN_PREFIX}gcc ${TOOLCHAIN_CFLAGS} -print-file-name=libgcc_s.so\``"
CPP_LIB_DIR="`dirname \`${TOOLCHAIN_PREFIX}gcc ${TOOLCHAIN_CFLAGS} -print-file-name=libstdc++.so\``"
CPPSUP_LIB_DIR="`dirname \`${TOOLCHAIN_PREFIX}gcc ${TOOLCHAIN_CFLAGS} -print-file-name=libsupc++.a\``"
CRT_FILES_DIR="`dirname \`${TOOLCHAIN_PREFIX}gcc ${TOOLCHAIN_CFLAGS} -print-file-name=crti.o\``"

# create output directories in a dash compatible way
for i in etc usr/bin sbin usr/sbin lib usr/lib usr/share usr/include
do
    mkdir -p $RPM_BUILD_ROOT/%{pfx}/$i
done

if [ -n "$PKG_LIBC_WANT_SHARED_LIBS" ]
then
    set +e
    cp -dp $SHARED_LIBS_DIR/*.so* $RPM_BUILD_ROOT/%{pfx}/lib/

    # Note: I think that the next copy line is really only needed for the
    #       linker script files libc.so and libpthread.so
    #       Don't do the next line for non sysroot uClibc toolchains as usr/lib
    #       is a symbolic link to lib! - Stevep
    if [ "${TC_TYPE}" != "UCLIBC" ]
    then
        cp -dp $SHARED_LIBS_DIR/../usr/lib/*.so* $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib/
    fi
    rm -f $RPM_BUILD_ROOT/%{pfx}/lib/libstdc++*.so*
    rm -f $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib/libstdc++*.so*
    rm -f $RPM_BUILD_ROOT/%{pfx}/lib/libgcc*.so*
    rm -f $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib/libgcc*.so*

    # Only needed if gcc native is selected.
    #
    # Future Note: ldd needs to have the path to the
    # lib directories in the staging area to prevent
    # prevent erroneous dependency failures especially for uclibc toolchain.
    rm -f $RPM_BUILD_ROOT/%{pfx}/lib/libgmp*.so*
    rm -f $RPM_BUILD_ROOT/%{pfx}/lib/libmpfr*.so*
    rm -f $RPM_BUILD_ROOT/%{pfx}/lib/libgomp*.so*

    if [ "$TC_TYPE" = "CSL" ]
    then
        i=`echo $STATIC_LIBS_DIR | perl -n -e 's,.*(libc)(/\w+)?/usr.*,, && print $1,$2'`
    elif [ "$TC_TYPE" = "EGLIBC" ]
    then
        i="sysroot"
    elif [ "$TC_TYPE" = "XTOOL-SYSROOT" ]
    then
        i="sys-root"
    else
        i=
    fi

    if [ -z "${UCLIBC}" ]
    then
        for file in catchsegv gencat getconf getent iconv ldd lddlibc4 locale localedef rpcgen sprof tzselect
        do
            if [ "$TC_TYPE" = "XTOOL" ]
            then
                cp -dpf $TC_PREFIX/$X_DIR/$i/bin/${file} $RPM_BUILD_ROOT/%{pfx}%{_prefix}/bin
            else
                cp -dpf $TC_PREFIX/$X_DIR/$i/usr/bin/${file} $RPM_BUILD_ROOT/%{pfx}%{_prefix}/bin
            fi
        done
        for file in ldconfig sln
        do
            cp -dpf $TC_PREFIX/$X_DIR/$i/sbin/${file} $RPM_BUILD_ROOT/%{pfx}/sbin
        done
        for file in convconfig build-locale-archive rpcinfo zdump zic
        do
            if [ "$TC_TYPE" = "XTOOL" ]
            then
                cp -dpf $TC_PREFIX/$X_DIR/$i/sbin/${file} $RPM_BUILD_ROOT/%{pfx}%{_prefix}/sbin
            else
                cp -dpf $TC_PREFIX/$X_DIR/$i/usr/sbin/${file} $RPM_BUILD_ROOT/%{pfx}%{_prefix}/sbin
            fi
        done
    else
        cp $TC_PREFIX/$X_DIR/$i/target_utils/ldd $RPM_BUILD_ROOT/%{pfx}%{_prefix}/bin
    fi
    set -e
fi

if [ -n "$PKG_LIBC_WANT_CRT_FILES" ]
then 
    cp -dp $CRT_FILES_DIR/*crt*.o $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib/
fi

if [ -n "$PKG_LIBC_WANT_HEADERS1" ]
then
    if [ "$TC_TYPE" = "CSL" ]
    then 
        cp -a $TC_PREFIX/$X_DIR/libc/usr/include $RPM_BUILD_ROOT/%{pfx}%{_prefix}
    elif [ "$TC_TYPE" = "EGLIBC" ]
    then
        cp -a $TC_PREFIX/$X_DIR/sysroot/usr/include $RPM_BUILD_ROOT/%{pfx}%{_prefix}
    elif [ "$TC_TYPE" = "XTOOL-SYSROOT" ]
    then
        cp -a $TC_PREFIX/$X_DIR/sys-root/usr/include $RPM_BUILD_ROOT/%{pfx}%{_prefix}
    elif [ "${TC_TYPE}" = "UCLIBC-SYSROOT" ]
    then
        cp -a ${TC_PREFIX}/usr/include ${RPM_BUILD_ROOT}/%{pfx}%{_prefix}
    else
        for i in $TC_PREFIX/$X_DIR/include $TC_PREFIX/include
        do
            if [ -f $i/stdio.h ]
            then
                cp -a $i $RPM_BUILD_ROOT/%{pfx}%{_prefix}
                break
            fi
        done
        rm -rf $RPM_BUILD_ROOT/%{pfx}%{_prefix}/include/c++
    fi
fi

if [ -n "$PKG_LIBC_WANT_STATIC_LIBS" ]
then 
    cp -dp $STATIC_LIBS_DIR/*.a $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib/
    rm -f $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib/libstdc++*a*
    rm -f $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib/libsupc++*a*
fi

if [ -n "$PKG_LIBC_WANT_C_LOCALES" ]
then
    set +e
    if [ -n "$UCLIBC" ]
    then
        cp -a $TC_PREFIX/usr/share/locale $RPM_BUILD_ROOT/%{pfx}%{_prefix}/share
    else
        if [ "$TC_TYPE" = "CSL" ]
        then
            i=`echo $STATIC_LIBS_DIR | perl -n -e 's,.*(libc)(/\w+)?(/usr).*,, && print $1,$2,$3'`

        elif [ "$TC_TYPE" = "EGLIBC" ]
        then
            i="sysroot/usr"
        elif [ "$TC_TYPE" = "XTOOL-SYSROOT" ]
        then
            i="sys-root/usr"
        else
            i=
        fi

        cp -a $TC_PREFIX/$X_DIR/$i/lib/locale $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib
        cp -a $TC_PREFIX/$X_DIR/$i/info $RPM_BUILD_ROOT/%{pfx}%{_prefix}
        cp -a $TC_PREFIX/$X_DIR/$i/share/locale $RPM_BUILD_ROOT/%{pfx}%{_prefix}/share
        cp -a $TC_PREFIX/$X_DIR/$i/share/i18n $RPM_BUILD_ROOT/%{pfx}%{_prefix}/share
        cp -a $TC_PREFIX/$X_DIR/$i/share/zoneinfo $RPM_BUILD_ROOT/%{pfx}%{_prefix}/share
        for j in tzselect locale localedef
        do
            cp -a $TC_PREFIX/$X_DIR/$i/bin/$j $RPM_BUILD_ROOT/%{pfx}%{_prefix}/bin/
        done
        cp -a $TC_PREFIX/$X_DIR/$i/$SLIBS/gconv $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib/
    fi
    set -e
fi

if [ -n "$PKG_CXX_WANT_SHARED_LIBS" ]
then
    # Note: The libstdc++ shared libraries really belong in rootfs/usr/lib
    #       but historically ltib has put them in rootfs/lib.  To minimize
    #       changes and potential problems they have been left in rootfs/lib
    #       for the time being.  - Stevep.
    set +e
    cp -dp $CPP_LIB_DIR/libstdc++*.so* $RPM_BUILD_ROOT/%{pfx}/lib/
    set -e
fi

if [ -n "$PKG_CXX_WANT_HEADERS" ]
then
    if [ "$TC_TYPE" = "CSL" -a -d $TC_PREFIX/$X_DIR/include/c++ ]
    then 
        i=$X_DIR
    elif [ "${TC_TYPE}" = "UCLIBC-SYSROOT" ]
    then
        i="usr/${X_DIR}"
    else
        i= 
    fi
    cp -a $TC_PREFIX/$i/include/c++ $RPM_BUILD_ROOT/%{pfx}%{_prefix}/include
fi

if [ -n "$PKG_CXX_WANT_STATIC_LIBS" ]
then 
    cp -dp $CPP_LIB_DIR/libstdc++*.a $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib/
    cp -dp $CPPSUP_LIB_DIR/libsupc++*.a $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib/
fi

if [ -n "$PKG_GCC_WANT_LIBGCC_SHARED" ]
then
    set +e
    cp -dp $GCC_SLIB_DIR/libgcc*.so* $RPM_BUILD_ROOT/%{pfx}/lib/
    set -e
fi


# remove absolute paths from text search files (if they exist)
perl -w -e '
    @ARGV = grep { `file $_` =~ m,ASCII\s+.*text, } @ARGV;
    exit(0) unless @ARGV;
    $^I = ".bak";
    while(<>) {
        s,[\S/]+/,,g if m,^GROUP,;
        print;
    }
    ' $RPM_BUILD_ROOT/%{pfx}/lib/libc.so \
      $RPM_BUILD_ROOT/%{pfx}/lib/libpthread.so \
      $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib/libc.so \
      $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib/libpthread.so

cd $RPM_BUILD_ROOT/%{pfx}
# this is necessary to avoid annoying warnings from ldd about no execute
# permissions for some malformed uClibc toolchains
find $RPM_BUILD_ROOT/%{pfx}/lib     | xargs chmod 755
find $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib | xargs chmod 755

# relocate all symlink .so (linker files) to usr/lib
cd lib
find . -name \*.so | perl -n -e '
   chomp;
   if(! -l && -f _  && m,(?:libpthread.so|libc.so)$, ) {
       print "Moving file $_ to ../usr/lib/\n";
       system("mv $_ ../usr/lib") == 0 or die;
   }
   next unless -l $_ ;
   $ltgt = readlink();
   $snam = substr($_, rindex($_, "/") + 1);
   if(! -l "../usr/lib/$snam") {
       print "Moving symlink $_ ($ltgt) to ../usr/lib/$snam\n";
       unlink $_;
       symlink("../../lib/$ltgt", "../usr/lib/$snam")
                    or die "symlink(../../lib/$ltgt, ../usr/lib/$snam) : $!\n";
   }
' 


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/lib/ld-2.13.so
%{pfx}/lib/ld-linux.so.3
%{pfx}/lib/libBrokenLocale-2.13.so
%{pfx}/lib/libBrokenLocale.so.1
%{pfx}/lib/libSegFault.so
%{pfx}/lib/libanl-2.13.so
%{pfx}/lib/libanl.so.1
%{pfx}/lib/libc-2.13.so
%{pfx}/lib/libc.so.6
%{pfx}/lib/libcidn-2.13.so
%{pfx}/lib/libcidn.so.1
%{pfx}/lib/libcrypt-2.13.so
%{pfx}/lib/libcrypt.so.1
%{pfx}/lib/libdl-2.13.so
%{pfx}/lib/libdl.so.2
%{pfx}/lib/libgcc_s.so
%{pfx}/lib/libgcc_s.so.1
%{pfx}/lib/libm-2.13.so
%{pfx}/lib/libm.so.6
%{pfx}/lib/libmemusage.so
%{pfx}/lib/libnsl-2.13.so
%{pfx}/lib/libnsl.so.1
%{pfx}/lib/libnss_compat-2.13.so
%{pfx}/lib/libnss_compat.so.2
%{pfx}/lib/libnss_dns-2.13.so
%{pfx}/lib/libnss_dns.so.2
%{pfx}/lib/libnss_files-2.13.so
%{pfx}/lib/libnss_files.so.2
%{pfx}/lib/libnss_hesiod-2.13.so
%{pfx}/lib/libnss_hesiod.so.2
%{pfx}/lib/libnss_nis-2.13.so
%{pfx}/lib/libnss_nis.so.2
%{pfx}/lib/libnss_nisplus-2.13.so
%{pfx}/lib/libnss_nisplus.so.2
%{pfx}/lib/libpcprofile.so
%{pfx}/lib/libpthread-2.13.so
%{pfx}/lib/libpthread.so.0
%{pfx}/lib/libresolv-2.13.so
%{pfx}/lib/libresolv.so.2
%{pfx}/lib/librt-2.13.so
%{pfx}/lib/librt.so.1
%{pfx}/lib/libstdc++.so.6
%{pfx}/lib/libstdc++.so.6.0.14
%{pfx}/lib/libthread_db-1.0.so
%{pfx}/lib/libthread_db.so.1
%{pfx}/lib/libutil-2.13.so
%{pfx}/lib/libutil.so.1
%{pfx}/sbin/ldconfig
%{pfx}/sbin/sln
%{pfx}/usr/bin/catchsegv
%{pfx}/usr/bin/gencat
%{pfx}/usr/bin/getconf
%{pfx}/usr/bin/getent
%{pfx}/usr/bin/iconv
%{pfx}/usr/bin/ldd
%{pfx}/usr/bin/locale
%{pfx}/usr/bin/localedef
%{pfx}/usr/bin/rpcgen
%{pfx}/usr/bin/sprof
%{pfx}/usr/bin/tzselect
%{pfx}/usr/lib/libBrokenLocale.so
%{pfx}/usr/lib/libanl.so
%{pfx}/usr/lib/libc.so
%{pfx}/usr/lib/libcidn.so
%{pfx}/usr/lib/libcrypt.so
%{pfx}/usr/lib/libdl.so
%{pfx}/usr/lib/libm.so
%{pfx}/usr/lib/libnsl.so
%{pfx}/usr/lib/libnss_compat.so
%{pfx}/usr/lib/libnss_dns.so
%{pfx}/usr/lib/libnss_files.so
%{pfx}/usr/lib/libnss_hesiod.so
%{pfx}/usr/lib/libnss_nis.so
%{pfx}/usr/lib/libnss_nisplus.so
%{pfx}/usr/lib/libpthread.so
%{pfx}/usr/lib/libresolv.so
%{pfx}/usr/lib/librt.so
%{pfx}/usr/lib/libstdc++.so
%{pfx}/usr/lib/libthread_db.so
%{pfx}/usr/lib/libutil.so
%{pfx}/usr/sbin/rpcinfo
%{pfx}/usr/sbin/zdump
%{pfx}/usr/sbin/zic
