%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : A helper application which loads modules for USB devices
Name            : hotplug
Version         : 2004_03_29
Release         : 3
License         : GPL
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : System Environment/Kernel
Source          : %{name}-%{version}.tar.gz
Patch1          : hotplug-2004_03_29-initd.patch
Patch2          : hotplug-2004_03_29-dash.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed hotplug for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Kernel
AutoReqProv     : no

%Description rfs
hotplug package contents restricted to just the files that are
needed at run time on the target.


%Description
%{summary}

%Prep
export LC_ALL
LC_ALL=C

%setup
%patch1 -p1
%patch2 -p1

%Build
export LC_ALL
LC_ALL=C

make

%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make install prefix=$RPM_BUILD_ROOT%{pfx}

cd %{_builddir}/%{name}-%{version}
( cd $RPM_BUILD_ROOT > /dev/null; find .%{pfx} \( \( -not -type d \) -o \( -type d -empty \) \) -print | sed 's/^\.//' ) > all_files.lst
sed '
    \,^%{pfx}%{_mandir}, d;
' all_files.lst > rfs_files.lst

%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files -f all_files.lst
%defattr(-,root,root)

%Files rfs -f rfs_files.lst
%defattr(-,root,root)
