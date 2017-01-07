%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Font configuration and customization library
Name            : fontconfig
Version         : 2.4.2
Release         : 1
License         : MIT
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : System Environment/Libraries
BuildRoot       : %{_tmppath}/%{name}
Prefix		: %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed fontconfig for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
AutoReqProv     : no

%Description rfs
fontconfig package contents restricted to just the files that
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

# Timestamp order is important.
for f in configure.ac configure.in aclocal.m4 configure config.h.in Makefile.am Makefile.in; do
	find . -name $f -exec touch {} \;
done
# we don't have docbook-utils in the distribution
ac_cv_prog_HASDOCBOOK=no \
ac_cv_prog_CC_FOR_BUILD="${BUILDCC}" \
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} \
            --with-arch=$GNUTARCH --sysconfdir=%{_sysconfdir} \
            --with-freetype-config="$DEV_IMAGE%{_prefix}/bin/freetype-config --prefix=$DEV_IMAGE%{_prefix}"
make


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT%{pfx} 

rm -rf $RPM_BUILD_ROOT%{pfx}%{_prefix}/lib/*.la
rm -rf $RPM_BUILD_ROOT%{pfx}%{_prefix}/share/doc
rm -rf $RPM_BUILD_ROOT%{pfx}%{_prefix}/lib/pkgconfig

perl -pi -e 's,^</fontconfig>,
<dir>%{_prefix}/X11R6/lib/X11/fonts/TTF</dir>
<dir>%{_prefix}/X11R6/lib/X11/fonts/Type1</dir>
<dir>%{_prefix}/X11R6/lib/X11/fonts/truetype</dir>
</fontconfig>
,;
        ' $RPM_BUILD_ROOT%{pfx}%{_sysconfdir}/fonts/local.conf


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/etc/fonts/conf.avail/10-autohint.conf
%{pfx}/etc/fonts/conf.avail/10-no-sub-pixel.conf
%{pfx}/etc/fonts/conf.avail/10-sub-pixel-bgr.conf
%{pfx}/etc/fonts/conf.avail/10-sub-pixel-rgb.conf
%{pfx}/etc/fonts/conf.avail/10-sub-pixel-vbgr.conf
%{pfx}/etc/fonts/conf.avail/10-sub-pixel-vrgb.conf
%{pfx}/etc/fonts/conf.avail/10-unhinted.conf
%{pfx}/etc/fonts/conf.avail/20-fix-globaladvance.conf
%{pfx}/etc/fonts/conf.avail/20-lohit-gujarati.conf
%{pfx}/etc/fonts/conf.avail/20-unhint-small-vera.conf
%{pfx}/etc/fonts/conf.avail/30-amt-aliases.conf
%{pfx}/etc/fonts/conf.avail/30-urw-aliases.conf
%{pfx}/etc/fonts/conf.avail/40-generic.conf
%{pfx}/etc/fonts/conf.avail/49-sansserif.conf
%{pfx}/etc/fonts/conf.avail/50-user.conf
%{pfx}/etc/fonts/conf.avail/51-local.conf
%{pfx}/etc/fonts/conf.avail/60-latin.conf
%{pfx}/etc/fonts/conf.avail/65-fonts-persian.conf
%{pfx}/etc/fonts/conf.avail/65-nonlatin.conf
%{pfx}/etc/fonts/conf.avail/69-unifont.conf
%{pfx}/etc/fonts/conf.avail/70-no-bitmaps.conf
%{pfx}/etc/fonts/conf.avail/70-yes-bitmaps.conf
%{pfx}/etc/fonts/conf.avail/80-delicious.conf
%{pfx}/etc/fonts/conf.avail/90-synthetic.conf
%{pfx}/etc/fonts/conf.d/20-fix-globaladvance.conf
%{pfx}/etc/fonts/conf.d/20-lohit-gujarati.conf
%{pfx}/etc/fonts/conf.d/20-unhint-small-vera.conf
%{pfx}/etc/fonts/conf.d/30-amt-aliases.conf
%{pfx}/etc/fonts/conf.d/30-urw-aliases.conf
%{pfx}/etc/fonts/conf.d/40-generic.conf
%{pfx}/etc/fonts/conf.d/49-sansserif.conf
%{pfx}/etc/fonts/conf.d/50-user.conf
%{pfx}/etc/fonts/conf.d/51-local.conf
%{pfx}/etc/fonts/conf.d/60-latin.conf
%{pfx}/etc/fonts/conf.d/65-fonts-persian.conf
%{pfx}/etc/fonts/conf.d/65-nonlatin.conf
%{pfx}/etc/fonts/conf.d/69-unifont.conf
%{pfx}/etc/fonts/conf.d/80-delicious.conf
%{pfx}/etc/fonts/conf.d/90-synthetic.conf
%{pfx}/etc/fonts/fonts.conf
%{pfx}/etc/fonts/fonts.dtd
%{pfx}/usr/bin/fc-cache
%{pfx}/usr/bin/fc-cat
%{pfx}/usr/bin/fc-list
%{pfx}/usr/bin/fc-match
%{pfx}/usr/lib/libfontconfig.so
%{pfx}/usr/lib/libfontconfig.so.1
%{pfx}/usr/lib/libfontconfig.so.1.2.0
%{pfx}/usr/var/cache/fontconfig
