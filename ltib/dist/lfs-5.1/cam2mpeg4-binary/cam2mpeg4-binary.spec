%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : cam2mpeg4
Name            : cam2mpeg4-binary-mx31
Version         : 1.0
Release         : 1
License         : Proprietary
Vendor          : Hantro Products Oy.
Packager        : John Faith
Group           : Applications/Test
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup 

%Build
# NOP

%Install
rm -rf $RPM_BUILD_ROOT
INSTALL_DIR=$RPM_BUILD_ROOT/%{pfx}/unit_tests
mkdir -p $INSTALL_DIR
cp cam2mpeg4.out $INSTALL_DIR

%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*


