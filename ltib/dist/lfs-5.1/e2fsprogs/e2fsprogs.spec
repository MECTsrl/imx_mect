%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary		: Second extended (ext2) filesystem and ext3 utilities
Name		: e2fsprogs
Version		: 1.41.4
Release		: 1
License		: GPL
Vendor		: Freescale
Packager	: Stuart Hughes, Emil Medve
Group		: System Environment/Base
URL		: http://e2fsprogs.sourceforge.net
BuildRoot	: %{_tmppath}/%{name}
Prefix		: %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed e2fsprogs for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Base
AutoReqProv     : no

%Description rfs
e2fsprogs package contents restricted to just the files that
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

# Timestamp order is important.
for f in configure.ac configure.in aclocal.m4 configure config.h.in Makefile.am Makefile.in; do
	find . -name $f -exec touch {} \;
done
BUILD_CC=$BUILDCC ./configure --host=$CFGHOST --enable-elf-shlibs
make


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT%{pfx} install install-libs


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-, root, root)
%{pfx}/*

%Files rfs
%defattr(-, root, root)
%{pfx}/etc/mke2fs.conf
%{pfx}/lib/libblkid.so.1
%{pfx}/lib/libblkid.so.1.0
%{pfx}/lib/libcom_err.so.2
%{pfx}/lib/libcom_err.so.2.1
%{pfx}/lib/libe2p.so.2
%{pfx}/lib/libe2p.so.2.3
%{pfx}/lib/libext2fs.so.2
%{pfx}/lib/libext2fs.so.2.4
%{pfx}/lib/libss.so.2
%{pfx}/lib/libss.so.2.0
%{pfx}/lib/libuuid.so.1
%{pfx}/lib/libuuid.so.1.2
%{pfx}/sbin/badblocks
%{pfx}/sbin/blkid
%{pfx}/sbin/debugfs
%{pfx}/sbin/dumpe2fs
%{pfx}/sbin/e2fsck
%{pfx}/sbin/e2image
%{pfx}/sbin/e2label
%{pfx}/sbin/e2undo
%{pfx}/sbin/findfs
%{pfx}/sbin/fsck
%{pfx}/sbin/fsck.ext2
%{pfx}/sbin/fsck.ext3
%{pfx}/sbin/fsck.ext4
%{pfx}/sbin/fsck.ext4dev
%{pfx}/sbin/logsave
%{pfx}/sbin/mke2fs
%{pfx}/sbin/mkfs.ext2
%{pfx}/sbin/mkfs.ext3
%{pfx}/sbin/mkfs.ext4
%{pfx}/sbin/mkfs.ext4dev
%{pfx}/sbin/resize2fs
%{pfx}/sbin/tune2fs
%{pfx}/usr/bin/chattr
%{pfx}/usr/bin/lsattr
%{pfx}/usr/bin/uuidgen
%{pfx}/usr/lib/e2initrd_helper
%{pfx}/usr/lib/libblkid.so
%{pfx}/usr/lib/libcom_err.so
%{pfx}/usr/lib/libe2p.so
%{pfx}/usr/lib/libext2fs.so
%{pfx}/usr/lib/libss.so
%{pfx}/usr/lib/libuuid.so
%{pfx}/usr/sbin/filefrag
%{pfx}/usr/sbin/mklost+found
%{pfx}/usr/sbin/uuidd
%{pfx}/usr/share/et/et_c.awk
%{pfx}/usr/share/et/et_h.awk
%{pfx}/usr/share/ss/ct_c.awk
%{pfx}/usr/share/ss/ct_c.sed
