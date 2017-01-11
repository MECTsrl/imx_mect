%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Wireless Ethernet configuration tools
Name            : wireless-tools
Version         : 29
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : System Environment/Base
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed %{name} for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Base
AutoReqProv     : no

%Description rfs
%{name} package contents restricted to just
the files that are needed at run time on the target.


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
make install PREFIX=$RPM_BUILD_ROOT/%{pfx}/%{_prefix}


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/lib/libiw.so
%{pfx}/usr/lib/libiw.so.29
%{pfx}/usr/sbin/ifrename
%{pfx}/usr/sbin/iwconfig
%{pfx}/usr/sbin/iwevent
%{pfx}/usr/sbin/iwgetid
%{pfx}/usr/sbin/iwlist
%{pfx}/usr/sbin/iwpriv
%{pfx}/usr/sbin/iwspy
