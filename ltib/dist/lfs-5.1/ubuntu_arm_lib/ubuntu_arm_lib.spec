%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Ubuntu arm user library for accessibility support
Name            : ubuntu_arm_lib
Version         : 1.0.3
Release         : 1
License         : Free BSD
Vendor          : Freescale
Packager        : Terry Lyu
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
Autoreq		: no
Autoreqprov	: no
Autoprov	: no
%Description
%{summary}

%Prep
%setup

%Build

%Install
rm -rf $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/ubuntu_arm_lib/
install -d $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/ubuntu_arm_lib
cp -rf * $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/ubuntu_arm_lib/

%Clean

%Files
%defattr(-,root,root)
%{pfx}/*


