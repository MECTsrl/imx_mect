%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Qwt package
Name            : qwt
Version         : 6.1.0
Release         : 1
License         : GNU LGPLv2.1
Vendor          : Qwt Widget Library
Packager        : Bergamaschini Emiliano
Group           : Development/Libraries
URL             : http://freefr.dl.sourceforge.net/project/qwt/qwt/6.0.1/%{name}-%{version}.tar.bz2
Source          : %{name}-%{version}.tar.bz2
Patch1          : qwt-6.0.1-1381834981.patch
Patch2          : qwt-6.1.0-1418122118.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no

#Patch1          : qwt-6.0.1-1381834981.patch : put libQtSVG dependent object under conditional compilation


%Package rfs
Summary         : Trimmed qwt for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Development/Libraries
AutoReqProv     : no

%Description rfs
qwt package contents restricted to just the files that are
needed at run time on the target.


%Description
%{summary}

%Prep
%setup
%patch1 -p1
%patch2 -p1 

%Build
cp qwt.pro qwt.pro.orig
awk '{if ($0 ~ /QwtDesigner/ || $0 ~ /QwtExamples/) {getline; getline;} else {print $0;}}' qwt.pro.orig > qwt.pro

cp qwtconfig.pri qwtconfig.pri.orig
awk '{if ($0 ~ /\/usr\/local\//) {print "    QWT_INSTALL_PREFIX    = /usr/";} else{print $0;}}' qwtconfig.pri.orig > qwtconfig.pri

/opt/Trolltech/bin/qmake -spec qws/linux-g++-mx

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
    INSTALL_ROOT=$RPM_BUILD_ROOT/%{pfx}\

cd %{_builddir}/%{name}-%{version}
( cd $RPM_BUILD_ROOT > /dev/null; find .%{pfx} \( \( -not -type d \) -o \( -type d -empty \) \) -print | sed 's/^\.//' ) > all_files.lst
sed '
    \,^%{pfx}%{_prefix}/doc, d;
    \,^%{pfx}%{_includedir}, d;
' all_files.lst > rfs_files.lst

%Clean
rm -rf $RPM_BUILD_ROOT

%Files -f all_files.lst
%defattr(-,root,root)


%Files rfs -f rfs_files.lst
%defattr(-,root,root)
