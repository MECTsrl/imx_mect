%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : DSP test binaries and download util for MPC8555AMC
Name            : mpc8555amc-dsputils
Version         : 1.3
Release         : 1
License         : BSD
Vendor          : Freescale
Packager        : John Traill
Group           : Utilities
Source          : mpc8555amc-dsputils-1.3.tar.bz2
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

MPC8555AMC DSP download util and test binaries

%Prep
%setup

%Build
gcc -o dsp dsp.c

%Install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}/root/dsputils
cp * $RPM_BUILD_ROOT/%{pfx}/root/dsputils

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
