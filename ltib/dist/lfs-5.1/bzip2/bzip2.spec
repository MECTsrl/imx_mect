%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : A file compression utility.
Name            : bzip2
Version         : 1.0.2
Release         : 2
License         : BSD
URL             : ftp://sources.redhat.com/pub/bzip2/v102/ 
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : Applications/File
Source          : %{name}-%{version}.tar.gz 
Patch0          : %{name}-%{version}-notest.patch
Patch1          : %{name}-%{version}-mandir.patch
Patch2          : %{name}-%{version}-armv7a-cross-compile-fix.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed bzip2 for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/File
AutoReqProv     : no

%Description rfs
bzip2 package contents restricted to just the files that are
needed at run time on the target.


%Description
%{summary}

%Prep
export LC_ALL
LC_ALL=C

%setup
%patch0 -p1
%patch1 -p1
%patch2 -p1

%Build
export LC_ALL
LC_ALL=C

make -f Makefile-libbz2_so
make clean
make

%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make install PREFIX=$RPM_BUILD_ROOT%{pfx}%{_prefix}

cd %{_builddir}/%{name}-%{version}
( cd $RPM_BUILD_ROOT > /dev/null; find .%{pfx} \( \( -not -type d \) -o \( -type d -empty \) \) -print | sed 's/^\.//' ) > all_files.lst
sed '
    \,^%{pfx}%{_prefix}/share/man, d;
    \,^%{pfx}%{_prefix}/include, d;
    /\.l\?a$/ d;
' all_files.lst > rfs_files.lst

%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files -f all_files.lst
%defattr(-,root,root)

%Files rfs -f rfs_files.lst
%defattr(-,root,root)
