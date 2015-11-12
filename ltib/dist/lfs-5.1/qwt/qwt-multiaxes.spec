%define pfx /opt/freescale/rootfs/%{_target_cpu}
%define variant multiaxes

Summary         : Qwt widget library with multiaxes capability
Name            : qwt
Version         : 6.1
Release         : 1_%{variant}
License         : GNU LGPLv2.1
Vendor          : Qwt Widget Library
Packager        : Mihai Lazarescu
Group           : Development/Libraries
URL             : svn://svn.code.sf.net/p/qwt/code/branches/%{name}-%{version}-%{variant}
Source          : %{name}-%{version}-%{variant}.tar.bz2
Patch1          : qwt-6.0.1-multiaxes-1381834981.patch
Patch2          : qwt-6.1.0-multiaxes-1418122118.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no

#Patch1          : qwt-6.0.1-1381834981.patch : put libQtSVG dependent object under conditional compilation


%Package rfs
Summary         : Trimmed for root file system requirements.
Group           : Development/Libraries
AutoReqProv     : no
%Description rfs
qwt-multiaxes package contents restricted to just the files
that are needed at run time on the target.


%Description
%{summary}

%Prep
%setup -n %{name}-%{version}-%{variant}
%patch1 -p1
%patch2 -p1 

%Build
cp qwt.pro qwt.pro.orig
awk '{if ($0 ~ /QwtDesigner/ || $0 ~ /QwtExamples/) {getline; getline;} else {print $0;}}' qwt.pro.orig > qwt.pro

cp qwtconfig.pri qwtconfig.pri.orig
awk '{if ($0 ~ /\/usr\/local\//) {print "    QWT_INSTALL_PREFIX    = /usr/";} else{print $0;}}' qwtconfig.pri.orig > qwtconfig.pri

/opt/Trolltech/bin/qmake -spec qws/linux-arm-gnueabi-g++

make \
    sub-src-all-ordered \
    sub-textengines-all-ordered \

%Install
rm -rf $RPM_BUILD_ROOT

make \
    install \
    sub-src-install_subtargets-ordered \
    sub-textengines-install_subtargets-ordered \
    install_qwtspec \
    INSTALL_ROOT=$RPM_BUILD_ROOT/%{pfx} \

( cd $RPM_BUILD_ROOT; find .%{pfx} \( \( -not -type d \) -o \( -type d -empty \) \) -print | sed 's/^\.//' ) > all_files.lst
sed '
    \,^%{pfx}%{_prefix}/features, d;
    \,^%{pfx}%{_includedir}, d;
    \,^%{pfx}%{_libdir}/pkgconfig, d;
' all_files.lst > rfs_files.lst

%Clean
rm -rf $RPM_BUILD_ROOT

%Files -f all_files.lst
%defattr(-,root,root)


%Files rfs -f rfs_files.lst
%defattr(-,root,root)
