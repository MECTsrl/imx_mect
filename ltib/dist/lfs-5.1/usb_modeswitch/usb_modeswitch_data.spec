%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Data for the USB Modeswitch tool
Name            : usb-modeswitch-data
Version         : 20160112
Release         : 1
License         : LGPL
Vendor          : MECT
Packager        : Mihai Lazarescu
Group           : Applications/System
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed down to just the run time files
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no

%Description rfs
%name} package contents trimmed to just the files
that are needed at run time on the target.


%Description
%{summary}.


%Prep
export LC_ALL
LC_ALL=C

%setup -T -c -n %{name}
cd ..; rmdir %{name}; ln -s ../../../projects/%{name} %{name}


%Build
export LC_ALL
LC_ALL=C


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}


# Compact the mode switching databse.
cd $RPM_BUILD_ROOT%{pfx}/usr/share/usb_modeswitch
BZIP2=-9 tar cjf %{_tmppath}/configPack.tar.bz2 *
rm -rf *
mv %{_tmppath}/configPack.tar.bz2 .


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/share/usb_modeswitch/configPack.tar.bz2
