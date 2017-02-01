%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : A library of functions for manipulating PNG image format files
Name            : libpng
Version         : 1.2.8
Release         : 1
License         : distributable, OSI approved
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : System Environment/Libraries
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed %{name} for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
AutoReqProv     : no

%Description rfs
%{name} package contents restricted to just the files that
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

make prefix=%{_prefix} -f scripts/makefile.linux


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

mkdir -p $RPM_BUILD_ROOT/%{pfx}/%{_prefix} 
make prefix=$RPM_BUILD_ROOT/%{pfx}/%{_prefix} install -f scripts/makefile.linux


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/lib/libpng.so
%{pfx}/usr/lib/libpng.so.3
%{pfx}/usr/lib/libpng.so.3.1.2.8
%{pfx}/usr/lib/libpng12.so
%{pfx}/usr/lib/libpng12.so.0
%{pfx}/usr/lib/libpng12.so.0.1.2.8
