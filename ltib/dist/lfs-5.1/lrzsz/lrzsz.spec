%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : The lrz and lsz modem communications programs.
Name            : lrzsz
Version         : 0.12.21
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Alan Tull
Group           : Applications/Communications
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no

%Package rfs
Summary         : Trimmed lrzsz for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/Communications
AutoReqProv     : no


%Description rfs
lrzsz package contents restricted to just the files that
are needed at run time on the target.

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

if [ -n "$UCLIBC" ]
then
    config_opts='ac_cv_lib_intl_gettext=no'
fi
# Timestamp order is important.
for f in configure.ac configure.in aclocal.m4 configure config.h.in Makefile.am Makefile.in; do
	find . -name $f -exec touch {} \;
done
eval $config_opts \
./configure --prefix=%{_prefix} --disable-pubdir --enable-syslog --program-transform-name=s/l// --cache-file=config.cache
touch Makefile.in
touch stamp-h.in
make -j1


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

make -j1 install DESTDIR=$RPM_BUILD_ROOT/%{pfx}


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/bin/rb
%{pfx}/usr/bin/rx
%{pfx}/usr/bin/rz
%{pfx}/usr/bin/sb
%{pfx}/usr/bin/sx
%{pfx}/usr/bin/sz
