%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : ISO code lists and translations
Name            : iso-codes
Version         : 3.3
Release         : 1
License         : LGPLv2+
Vendor          : UNKNOWN(Freescale)
Packager        : UNKNOWN(LTIB addsrpms)
Group           : System Environment/Base
URL             : http://alioth.debian.org/projects/pkg-isocodes/
Source          : iso-codes-3.3.tar.bz2
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

NOTE: this was imported by ltib -m addsrpms iso-codes-3.3-1.fc10.src.rpm

%Prep
%setup -q


%Build
%configure
make


%Install
%{__rm} -rf $RPM_BUILD_ROOT/%{pfx}/
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}/

%find_lang iso-codes --all-name


%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
