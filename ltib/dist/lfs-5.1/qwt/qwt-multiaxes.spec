%define pfx /opt/freescale/rootfs/%{_target_cpu}
%define variant multiaxes

Summary         : Qwt widget library with multiaxes capability
Name            : qwt-multiaxes
Version         : 6.1
Release         : 1_%{variant}
License         : GNU LGPLv2.1
Vendor          : Qwt Widget Library
Packager        : Mihai Lazarescu
Group           : Development/Libraries
URL             : svn://svn.code.sf.net/p/qwt/code/branches/qwt-%{version}-%{variant}
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Development/Libraries
AutoReqProv     : no

%Description rfs
qwt-multiaxes package contents restricted to just the files
that are needed at run time on the target.


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

../../host_tools/Trolltech/bin/qmake -spec qws/linux-g++-mx

make \
    sub-src-all-ordered \
    sub-textengines-all-ordered \


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

make \
    install \
    sub-src-install_subtargets-ordered \
    sub-textengines-install_subtargets-ordered \
    install_qwtspec \
    INSTALL_ROOT=$RPM_BUILD_ROOT/%{pfx} \


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/lib/libqwt.so
%{pfx}/usr/lib/libqwt.so.6
%{pfx}/usr/lib/libqwt.so.6.3
%{pfx}/usr/lib/libqwt.so.6.3.0
%{pfx}/usr/lib/libqwtmathml.so
%{pfx}/usr/lib/libqwtmathml.so.6
%{pfx}/usr/lib/libqwtmathml.so.6.3
%{pfx}/usr/lib/libqwtmathml.so.6.3.0
