%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Tool for extracting and viewing files in .zip archives.
Name            : unzip
Version         : 5.52
Release         : 1
License         : BSD
Vendor          : Freescale
Packager        : John Rigby
Group           : Applications/File
URL             : http://infozip.sourcforge.net
Source          : unzip552.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed unzip for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/File
AutoReqProv     : no

%Description rfs
unzip package contents restricted to just the files that are
needed at run time on the target.


%Description
%{summary}

%Prep
export LC_ALL
LC_ALL=C

%setup -n unzip-5.52

%Build
export LC_ALL
LC_ALL=C

make -f unix/Makefile linux_noasm
make

%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make install prefix=$RPM_BUILD_ROOT/%{pfx}/%{_prefix}

cd %{_builddir}/%{name}-%{version}
( cd $RPM_BUILD_ROOT > /dev/null; find .%{pfx} \( \( -not -type d \) -o \( -type d -empty \) \) -print | sed 's/^\.//' ) > all_files.lst
sed '
    \,^%{pfx}/usr/man, d;
' all_files.lst > rfs_files.lst

%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files -f all_files.lst
%defattr(-,root,root)

%Files rfs -f rfs_files.lst
%defattr(-,root,root)
