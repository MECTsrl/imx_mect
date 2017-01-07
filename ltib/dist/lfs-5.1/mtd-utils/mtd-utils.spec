%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary		: Memory Technology Device tools
Name		: mtd-utils
Version		: 201006
Release		: 1
License		: GPL
Vendor		: Freescale Semiconductor
Packager	: Ross Wille
Group		: Applications/System
%ifnarch arm
Source		: %{name}-%{version}.tar.bz2
Patch1          : mtd-utils-201006-4K-218-224-support.patch
Patch2          : mtd-utils-201006-1418122799.patch
Patch3          : mtd-utils-gcc_v5.4.patch
%endif
BuildRoot	: %{_tmppath}/%{name}
Prefix		: %{pfx}
AutoReqProv     : no


%ifarch arm

%Package rfs
Summary         : Trimmed mtd-utils for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no

%Description rfs
mtd-utils package contents restricted to just the files that are
needed at run time on the target.

%endif


%Description
%{summary}

Sources extracted from git tree: 
  git clone git://git.infradead.org/mtd-utils.git
  SHA1 d769da93a56590c23ce9430a1d970e31e835ae88


%Prep
export LC_ALL
LC_ALL=C

%ifnarch arm

%setup -n %{name}
%patch1 -p1
%patch2 -p1

if test "$(lsb_release -r | cut -f2 | cut -d. -f1)" -gt 14; then
%patch3 -p1
fi

%else

%setup -T -c -n %{name}
cd ..; rmdir %{name}; ln -s ../../../projects/%{name} %{name}

%endif


%Build
export LC_ALL
LC_ALL=C

make -j1 WITHOUT_XATTR=1


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make -j1 DESTDIR=$RPM_BUILD_ROOT%{pfx} SBINDIR=%{_prefix}/bin MANDIR=%{_mandir} install

mkdir -p $RPM_BUILD_ROOT%{pfx}%{_prefix}/include/mtd
install -m 0644 include/mtd/*.h $RPM_BUILD_ROOT%{pfx}%{_prefix}/include/mtd

cd $RPM_BUILD_ROOT


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%ifarch arm

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/bin/bin2nand
%{pfx}/usr/bin/doc_loadbios
%{pfx}/usr/bin/docfdisk
%{pfx}/usr/bin/flash_erase
%{pfx}/usr/bin/flash_eraseall
%{pfx}/usr/bin/flash_info
%{pfx}/usr/bin/flash_lock
%{pfx}/usr/bin/flash_otp_dump
%{pfx}/usr/bin/flash_otp_info
%{pfx}/usr/bin/flash_unlock
%{pfx}/usr/bin/flashcp
%{pfx}/usr/bin/ftl_check
%{pfx}/usr/bin/ftl_format
%{pfx}/usr/bin/jffs2dump
%{pfx}/usr/bin/mkbootenv
%{pfx}/usr/bin/mkpfi
%{pfx}/usr/bin/mtd_debug
%{pfx}/usr/bin/mtdinfo
%{pfx}/usr/bin/nand2bin
%{pfx}/usr/bin/nanddump
%{pfx}/usr/bin/nandtest
%{pfx}/usr/bin/nandwrite
%{pfx}/usr/bin/nftl_format
%{pfx}/usr/bin/nftldump
%{pfx}/usr/bin/pddcustomize
%{pfx}/usr/bin/pfi2bin
%{pfx}/usr/bin/pfiflash
%{pfx}/usr/bin/recv_image
%{pfx}/usr/bin/rfddump
%{pfx}/usr/bin/rfdformat
%{pfx}/usr/bin/serve_image
%{pfx}/usr/bin/sumtool
%{pfx}/usr/bin/ubiattach
%{pfx}/usr/bin/ubicrc32
%{pfx}/usr/bin/ubicrc32.pl
%{pfx}/usr/bin/ubidetach
%{pfx}/usr/bin/ubiformat
%{pfx}/usr/bin/ubigen
%{pfx}/usr/bin/ubimirror
%{pfx}/usr/bin/ubimkvol
%{pfx}/usr/bin/ubinfo
%{pfx}/usr/bin/ubinize
%{pfx}/usr/bin/ubirename
%{pfx}/usr/bin/ubirmvol
%{pfx}/usr/bin/ubirsvol
%{pfx}/usr/bin/ubiupdatevol
%{pfx}/usr/bin/unubi

%endif
