%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : X.Org X server -- i.MX accelerated video driver
Name            : xserver-xorg-video-imx
Version         : 2.6.35.3
Release         : 1.1.0
License         : X11
Vendor          : Freescale
Packager        : Rob Herring
Group           : System Environment/Libraries
Source          : %{name}-%{version}-%{release}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description

%Prep
%setup -n %{name}-%{version}-%{release}

%Build
export CFLAGS="-I$DEV_IMAGE/usr/src/linux/include"
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}

make

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
find $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/ -name "*.la" | xargs rm -f

install -d $RPM_BUILD_ROOT/%{pfx}/etc/X11
cat <<EOF > $RPM_BUILD_ROOT/%{pfx}/etc/X11/xorg.conf
Section "InputDevice"
	Identifier	"Generic Keyboard"
	Driver		"kbd"
	Option		"XkbRules"	"xorg"
	Option		"XkbModel"	"pc105"
	Option		"XkbLayout"	"us"
EndSection

Section "InputDevice"
	Identifier	"Configured Mouse"
	Driver		"mouse"
	Option		"CorePointer"
EndSection

Section "Device"
	Identifier	"i.MX Accelerated Framebuffer Device"
	Driver		"imx"
	Option		"fbdev"		"/dev/fb0"

# This option only recognized when "mxc_epdc_fb" frame buffer driver in
# use.  Values are "RGB565" (default, 16-bit RGB), "Y8" (8-bit gray),
# and "Y8INV" (8-bit gray inverted).
	Option		"FormatEPDC"	"Y8INV"

EndSection

Section "Monitor"
	Identifier	"Configured Monitor"
EndSection

Section "Screen"
	Identifier	"Default Screen"
	Monitor		"Configured Monitor"
	Device		"i.MX Accelerated Framebuffer Device"
EndSection

Section "ServerLayout"
	Identifier	"Default Layout"
	Screen		"Default Screen"
EndSection

EOF

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*

