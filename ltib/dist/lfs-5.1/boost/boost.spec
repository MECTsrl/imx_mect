%define pfx /opt/freescale/rootfs/%{_target_cpu}
%define __unzip unzip -a

Summary         : c++ libraries
Name            : boost
Version         : 1.31.0
Release         : 1
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : System Environment/Libraries
Source          : %{name}_1_31_0.tar.bz2
Patch0          : boost-1.31.0-regex-patch-20040503.zip
License         : Boost (distributable)
BuildRoot       : %{_tmppath}/%{name}

%Description
%{summary}

%Prep
%setup -n %{name}_1_31_0
cd $RPM_BUILD_DIR/%{name}_1_31_0/boost/regex/v4
%{__unzip} -o $RPM_SOURCE_DIR/boost-1.31.0-regex-patch-20040503.zip

%Build


%Install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}/%{_prefix}
(cd tools/build/jam_src && ./build.sh)
BJAM=`find tools/build/jam_src/ -name bjam -a -type f`
PYTHON_VERSION=`python -V 2>&1 |sed 's,.* \([0-9]\.[0-9]\)\(\.[0-9]\)\?.*,\1,'`
PYTHON_FLAGS="-sPYTHON_ROOT=%{_prefix} -sPYTHON_VERSION=$PYTHON_VERSION"
$BJAM $PYTHON_FLAGS -sTOOLS=gcc -sBUILD="debug release" --prefix=$RPM_BUILD_ROOT/%{pfx} %{_prefix} install


%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*
