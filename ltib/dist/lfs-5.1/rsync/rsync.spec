%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : A program for synchronizing files over a network
Name            : rsync
Version         : 2.6.5
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : Applications/Internet
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed rsync for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/Internet
AutoReqProv     : no

%Description rfs
rsync package contents restricted to just the files that are
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
rsync_cv_HAVE_GETTIMEOFDAY_TZ=yes \
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make install prefix=$RPM_BUILD_ROOT/%{pfx}/%{_prefix}


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/bin/rsync
