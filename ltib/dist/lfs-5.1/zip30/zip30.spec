%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : A file compression utility.
Name            : zip
Version         : 3.0.0
Release         : 0
License         : BSD
Vendor          : Mect srl
Packager        : Monica Donno
Group           : Applications/File
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed zip to just the runtimes needed on the root file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/File
AutoReqProv     : no

%Description rfs
zip package contents restricted to just the files that are
needed at run time on the target.


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

make -f unix/Makefile generic_gcc


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make -f unix/Makefile install PREFIX=$RPM_BUILD_ROOT/%{pfx}/%{_prefix}
$TOOLCHAIN_PATH/bin/${TOOLCHAIN_PREFIX}strip --strip-unneeded $RPM_BUILD_ROOT/%{pfx}%{_prefix}/bin/zip


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/bin/zip
