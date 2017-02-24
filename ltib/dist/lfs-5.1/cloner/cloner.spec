%define pfx /opt/freescale/rootfs/%{_target_cpu}


Summary         : Clone/restore MECT TPAC software
Name            : cloner
Version         : 2.1.0
Release         : 1
License         : GPL
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System/Tools
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed %{name} for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System/Tools
AutoReqProv     : no

%Description rfs
%{name} package contents limited to just the files
needed at run time on the target.


%Description
Graphical stand-alone tool that allow to clone and restore
all software and configuration of an i.MX28-based TPAC device.


%Prep
export LC_ALL
LC_ALL=C

%setup -T -c -n %{name}
cd ..; rmdir %{name}; ln -s ../../../projects/%{name} %{name}


%Build
export LC_ALL
LC_ALL=C

export VERSION='\"%{version}\"'
${DEV_IMAGE}/usr/bin/qmake -spec qws/linux-g++-mx
make


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

install -m 755 -D cloner $RPM_BUILD_ROOT%{pfx}/sbin/cloner
install -m 644 -D excludes_localfs.lst $RPM_BUILD_ROOT%{pfx}/usr/share/cloner/excludes_localfs.lst
install -m 644 -D excludes_rootfs.lst $RPM_BUILD_ROOT%{pfx}/usr/share/cloner/excludes_rootfs.lst

%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/sbin/cloner
%{pfx}/usr/share/cloner/excludes_localfs.lst
%{pfx}/usr/share/cloner/excludes_rootfs.lst
