%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : XML 1.0 parser
Name            : expat
Version         : 1.95.8
Release         : 1
License         : MIT/X Consortium License
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : Applications/Publishing/XML
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed expat for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/Publishing/XML
AutoReqProv     : no

%Description rfs
expat package contents restricted to just the files that are
needed at run time on the target.


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

# Timestamp order is important.
for f in configure.ac configure.in aclocal.m4 configure config.h.in Makefile.am Makefile.in; do
	find . -name $f -exec touch {} \;
done
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} --mandir=%{_mandir}
make


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT%{pfx} install


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/bin/xmlwf
%{pfx}/usr/lib/libexpat.so
%{pfx}/usr/lib/libexpat.so.0
%{pfx}/usr/lib/libexpat.so.0.5.0
