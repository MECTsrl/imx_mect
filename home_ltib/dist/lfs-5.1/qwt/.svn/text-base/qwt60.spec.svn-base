%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Qwt package
Name            : qwt
Version         : 6.0.1
Release         : z
License         : GPL
Vendor          : Mect
Packager        : Bergamaschini Emiliano
Group           : xxxx
URL             : http://freefr.dl.sourceforge.net/project/qwt/qwt/6.0.1/qwt-6.0.1.tar.bz2
Source          : %{name}-%{version}.tar.bz2
Patch1          : qwt-6.0.1-1381834981.patch
Patch2          : qwt-6.0.1-1397544751.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

#Patch1          : qwt-6.0.1-1381834981.patch : put libQtSVG dependent object under conditional compilation
#Patch2          : qwt-6.0.1-1397544751.patch : applied patch Qwt6.0.1_10AxisPerSide.patch to be built with ltib.

%Description
%{summary}

%Prep
%setup
%patch1 -p1
%patch2 -p1 

%Build
cp qwt.pro qwt.pro.ori
awk '{if ($0 ~ /QwtDesigner/ || $0 ~ /QwtExamples/) {getline; getline;} else {print $0;}}' qwt.pro.ori > qwt.pro
cp qwtconfig.pri qwtconfig.pri.ori
awk '{if ($0 ~ /\/usr\/local\//) {print "    QWT_INSTALL_PREFIX    = /usr/";} else{print $0;}}' qwtconfig.pri.ori > qwtconfig.pri
/usr/local/Trolltech/Qt-qvfb-version/bin/qmake -spec qws/linux-arm-gnueabi-g++
#./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make sub-src-all-ordered sub-textengines-all-ordered

%Install
rm -rf $RPM_BUILD_ROOT
make install sub-src-install_subtargets-ordered sub-textengines-install_subtargets-ordered install_qwtspec INSTALL_ROOT=$RPM_BUILD_ROOT/%{pfx}
# clean documentation
rm -rf $RPM_BUILD_ROOT/%{pfx}/qwt-6.0.1/doc

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
