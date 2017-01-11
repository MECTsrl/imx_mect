%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : CSR wifi driver source code
Name            : csr-wifi-src
Version         : 2.6.35.3
Release         : 1.1.0
License         : Proprietary
Vendor          : CSR
Packager        : Sam Yang
Group           : System/Servers
Source          : %{name}-%{version}-%{release}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
This package provides proprietary kernel modules, libraries, and
test code source from the CSR wifi driver.

%{summary}

%Prep
%setup -n %{name}-%{version}-%{release}

%Build
# build the libraries and kernel modules 
./build.sh $PWD/../linux

%Install
SOC=$(echo $PLATFORM | cut -d_ -f1 | cut -c2-)
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}

KERNEL_VER=`perl -e '
    foreach  ( glob("$ENV{DEV_IMAGE}/lib/modules/*") ) {
        next unless -d $_;
        if( m,/lib/modules/(\d\.\d[\S]+), ) {
            print $1;
            last;
        }
    } '`

./install.sh $RPM_BUILD_ROOT/%{pfx} $KERNEL_VER

# Package up the build results and leave in rpm/SOURCES for csr-wifi-bin spec file
rm -rf csr-wifi-bin-${SOC}-%{version}
mkdir csr-wifi-bin-${SOC}-%{version}
mv $RPM_BUILD_ROOT/%{pfx}/* csr-wifi-bin-${SOC}-%{version}
tar -zcf csr-wifi-bin-${SOC}-%{version}.tar.gz csr-wifi-bin-${SOC}-%{version}
# todo fix this to use rpmdir or something better than TOP:
cp -f csr-wifi-bin-${SOC}-%{version}.tar.gz $TOP/rpm/RPMS/"$LINTARCH"
cp -f csr-wifi-bin-${SOC}-%{version}.tar.gz $TOP/rpm/SOURCES

# Now delete everything we just tarred up.  csr-wifi-bin spec file will install it.
rm -rf $RPM_BUILD_ROOT/%{pfx}
# Create an empty directory for rpm to have something install or it won't be happy.
mkdir -p $RPM_BUILD_ROOT/%{pfx}/usr



%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(755,root,root)
%{pfx}/*
