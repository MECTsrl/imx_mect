%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : GStreamer Plugins Base
Name            : gst-plugins-base
Version         : 0.10.35
Release         : 1
License         : LGPL
Vendor          : Freescale
Packager        : Kurt Mahan, Dexter Ji
Group           : Applications/System
Source          : %{name}0.10_%{version}.orig.tar.bz2
Patch1          : %{name}-0.10.12-relink.patch
Patch2          : %{name}0.10_%{version}-gstplaybin2_rawvideo_support.patch
Patch3          : %{name}0.10_%{version}-fix-gstaudiobuild.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup
%patch1 -p1
%patch2 -p1
%patch3 -p1


%Build
export NM=nm
if [ -z "$PKG_LIBX11" ]
then
    XTRA_OPTS="$XTRA_OPTS --without-x"
fi
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} \
	    --disable-vorbis --disable-vorbistest --disable-freetypetest \
	    --disable-theora --disable-ogg --disable-oggtest --disable-pango\
	    --disable-libvisual --disable-cdparanoia --disable-failing-tests --disable-examples $XTRA_OPTS
make


%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
find $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/ -name "*.la" | xargs rm -f

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*
