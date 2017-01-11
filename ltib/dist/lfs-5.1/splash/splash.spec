%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : HMI splash screen
Name            : splash
Version         : 1.0
Release         : 1
License         : GPL
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/File
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed %{name} to just runtimes
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/File
AutoReqProv     : no

%Description rfs
%{name} package contents limited to just the files
needed at run time on the target system.


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

test -r Makefile && make clean
/opt/Trolltech/bin/qmake -spec qws/linux-g++-mx
make -j1


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

install -D -m 0755 splash $RPM_BUILD_ROOT%{pfx}/usr/bin/splash


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/bin/splash
