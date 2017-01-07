%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : cantest
Name            : cantest
Version         : 1.0
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Chen Hongjun
Group           : Applications/System
URL             : http://svn.berlios.de/svnroot/repos/socketcan/trunk/can-utils/
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed cantest for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no

%Description rfs
cantest package contents restricted to just the files that
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

make


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT%{pfx}%{_prefix}/bin
cp cantest $RPM_BUILD_ROOT%{pfx}%{_prefix}/bin


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/bin/cantest
