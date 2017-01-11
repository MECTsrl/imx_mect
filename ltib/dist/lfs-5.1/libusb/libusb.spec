%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : A library which allows userspace access to USB devices 
Name            : libusb
Version         : 0.1.8
Release         : 1
License         : LGPL
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed libusb for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
AutoReqProv     : no

%Description rfs
libusb package contents restricted to just the files that are
needed at run time on the target.


%Description
%{summary}

%Prep
export LC_ALL
LC_ALL=C

%setup 
libtoolize --copy --force

%Build
export LC_ALL
LC_ALL=C

# note: I tried version 0.1.10a buy this requires a c++ compiler

# configure can't figure this out in my environment (cross)
ENDIAN=${ENDIAN:-big}
case $ENDIAN in 
   big) conf_opts="ac_cv_c_bigendian=yes" ;;
   *)   conf_opts="ac_cv_c_bigendian=no"  ;;
esac

./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} --disable-build-docs  $conf_opts
make

%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}

cd %{_builddir}/%{name}-%{version}
( cd $RPM_BUILD_ROOT > /dev/null; find .%{pfx} \( \( -not -type d \) -o \( -type d -empty \) \) -print | sed 's/^\.//' ) > all_files.lst
sed '
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
