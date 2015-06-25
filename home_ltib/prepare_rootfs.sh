#!/bin/sh

DELETED="../deleted_files.txt"
QT="Y"

echo adding dropbear key
sudo cp dropbear_rsa_host_key rootfs/etc/dropbear/dropbear_rsa_host_key

echo adding Sourcery gdbserver
sudo cp /home/imx28/CodeSourcery/Sourcery_G++_Lite/arm-none-linux-gnueabi/libc/usr/bin/gdbserver rootfs/usr/bin

echo prepare /dev
sudo tar xjf dev.tar.bz2 -C rootfs/

echo "deleting usr/local/Trolltech"
echo rootfs/usr/local/Trolltech >> $DELETED
sudo rm -rf rootfs/usr/local/Trolltech

echo "deleting usr/lib/qt.tar"
echo rootfs/usr/lib/qt.tar >> $DELETED
sudo rm -rf rootfs/usr/lib/qt.tar

echo "deleting rootfs/usr/lib/fonts.tar"
echo rootfs/usr/lib/fonts.tar >> $DELETED
sudo rm -rf rootfs/usr/lib/fonts.tar

echo "excluding header files..."
if [ "`find rootfs -name include | wc -l`" -ne "0" ]
then
	find rootfs -name include >> $DELETED
	find rootfs -name include | sudo xargs tar cf tmp_include.tar
	find rootfs -name include | sudo xargs rm -rf
fi
if [ "`find rootfs -name \*.h | wc -l`" -ne "0" ]
then
	find rootfs -name \*.h >> $DELETED
	find rootfs -name \*.h | sudo xargs tar cf tmp_h.tar
	find rootfs -name \*.h | sudo xargs rm -rf
fi

echo "Finding if current kernel is realtime..."
CURR_KERN_FILE=config/platform/imx/.config
CURR_KERN=`grep CONFIG_KERNEL_35_IPIPE  $CURR_KERN_FILE | cut -d'=' -f2`
if [ "$CURR_KERN" = "y" ]; then
	CURR_KERN_VER="_ipipe"
else
	CURR_KERN_VER=""
fi


cd rootfs

echo "moving boot directory"
sudo mv boot ..

echo "moving boot_ipipe directory"
sudo mv boot_ipipe ..

echo "moving local directory"
sudo mv local ..
sudo mkdir local

echo "Size of rootfs:"
du -hs .

echo "deleting static library..."
find . -name \*.a > $DELETED
find . -name \*.a | grep -v socketlib  | grep -v tslib | sudo xargs rm -rf

#echo "choosing library..."
echo usr/lib/libQtTest* >> $DELETED
sudo rm -rf usr/lib/libQtTest*
echo usr/lib/libQt3Support* >> $DELETED
sudo rm -rf usr/lib/libQt3Support*
echo usr/lib/libQtWebKit* >> $DELETED
sudo rm -rf usr/lib/libQtWebKit*

#echo "deleting header files..."
#find . -name include >> $DELETED
#find . -name include | sudo xargs rm -rf
#find . -name \*.h >> $DELETED
#find . -name \*.h | sudo xargs rm -rf

echo "deleting html files..."
find . -name \*.htm* >> $DELETED
find . -name \*.htm* | sudo xargs rm -rf

echo "deleting man files..."
find . -name man >> $DELETED
find . -name man | sudo xargs rm -rf

echo "deleting locales..."
echo "usr/share/locale" >> $DELETED
sudo rm -rf usr/share/locale

echo "deleting icons..."
echo "usr/icons" >> $DELETED
sudo rm -rf usr/icons

echo "deleting ubi command..."
#echo usr/bin/ubi* >> $DELETED
#sudo rm usr/bin/ubi*
#echo usr/bin/unubi >> $DELETED
#sudo rm usr/bin/unubi

echo "deleting nand command..."
#echo usr/bin/nand* >> $DELETED
#sudo rm usr/bin/nand*
#echo usr/bin/flash_* >> $DELETED
#sudo rm usr/bin/flash_*
#echo "usr/bin/kobs-ng" >> $DELETED
#sudo rm -f usr/bin/kobs-ng

echo "deleting other files..."
find . -name gtk-doc >> $DELETED
find . -name gtk-doc | sudo xargs rm -rf
find . -name htdocs >> $DELETED
find . -name htdocs | sudo xargs rm -rf
find . -name example >> $DELETED
find . -name example | sudo xargs rm -rf
find . -name examples >> $DELETED
find . -name examples | sudo xargs rm -rf
find . -name doc >> $DELETED
find . -name doc | sudo xargs rm -rf
find . -name demo >> $DELETED
find . -name demo | sudo xargs rm -rf
find . -name demos >> $DELETED
find . -name demos | sudo xargs rm -rf
find . -name manual >> $DELETED
find . -name manual | sudo xargs rm -rf
find . -name info >> $DELETED
find . -name info | sudo xargs rm -rf
echo "usr/lib/pkgconfig" >> $DELETED
sudo rm -rf usr/lib/pkgconfig
echo "usr/share/terminfo" >> $DELETED
sudo rm -rf usr/share/terminfo
echo usr/bin/mkfs* >> $DELETED
sudo rm -f usr/bin/mkfs*
#echo usr/bin/gdb* >> $DELETED
#sudo rm -f usr/bin/gdb*
echo "var/lib/rpm/*" >> $DELETED
sudo rm -rf var/lib/rpm/*
#echo "lib/modules" >> $DELETED
#sudo rm -rf lib/modules
echo "deleting unit_tests ..."
echo "unit_tests" >> $DELETED
sudo rm -rf unit_tests

echo "cleaning xenomai..."
echo "deleting xenomai include and share ...."
sudo rm -rf usr/xenomai/include
echo "usr/xenomai/include" >> $DELETED
sudo rm -rf usr/xenomai/share/doc
echo "usr/xenomai/share/doc" >> $DELETED
sudo rm -rf usr/xenomai/share/man
echo "usr/xenomai/share/man" >> $DELETED

if [ "$CURR_KERN_VER" = "_ipipe" ]; then
	echo "moving unused modules directory lib/modules/2.6.35.3-744-g27fdf7b..."
	sudo mv lib/modules/2.6.35.3-744-g27fdf7b ..
else
	echo "moving unused modules directory lib/modules/2.6.35.3-744-g27fdf7b_ipipe..."
	sudo mv lib/modules/2.6.35.3-744-g27fdf7b_ipipe ..
	echo "moving unused xenomai..."
	sudo mv usr/xenomai ..
fi

if [ "$QT" = "N" ]
then
	echo "removing QT libraries"
	sudo rm -rf usr/lib/libQt*
fi

echo "Size of rootfs:"
du -hs .

echo "preparing rootfs.tar.bz2"
rm -f ../rootfs.tar.bz2
tar cjf ../rootfs.tar.bz2 *

cd ..

echo "preparing local local.tar.bz2"
rm -f local.tar.bz2
cd local
tar cjf ../local.tar.bz2 *
cd ..

echo "restoring modules"

if [ "$CURR_KERN_VER" = "_ipipe" ]; then
	sudo mv 2.6.35.3-744-g27fdf7b rootfs/lib/modules
else
	sudo mv 2.6.35.3-744-g27fdf7b_ipipe rootfs/lib/modules
	echo "restoring xenomai"
	sudo mv xenomai rootfs/usr
fi

echo "restoring boot directory"
sudo mv boot rootfs

echo "restoring boot_ipipe directory"
sudo mv boot_ipipe rootfs

echo "restoring local directory"
sudo rm -rf rootfs/local
sudo mv local rootfs

echo "restoring includes"
if [ -e tmp_include.tar ]
then
	sudo tar xf tmp_include.tar
	sudo rm -rf tmp_include.tar
fi
if [ -e tmp_h.tar ]
then
	sudo tar xf tmp_h.tar
	sudo rm -rf tmp_h.tar
fi

echo "done"

#cp -i rootfs.tar.bz2 $HOME/Desktop/MFGToolsProfiles/MX28\ Linux\ Update\ Evk/OS\ Firmware/files/
#cp -i local.tar.bz2 $HOME/Desktop/MFGToolsProfiles/MX28\ Linux\ Update\ Evk/OS\ Firmware/files/
#cp -i rootfs/boot/imx28_ivt_linux.sb $HOME/Desktop/MFGToolsProfiles/MX28\ Linux\ Update\ Evk/OS\ Firmware/files/

#cp -i rootfs.tar.bz2 /home/mect/ltib/mfg_tools_file/
#cp -i local.tar.bz2 /home/mect/ltib/mfg_tools_file/

#if [ "$CURR_KERN_VER" = "_ipipe" ]; then
#	cp -i rootfs/boot_ipipe/imx28_ivt_linux.sb /home/mect/ltib/mfg_tools_file/
#else
#	cp -i rootfs/boot/imx28_ivt_linux.sb /home/mect/ltib/mfg_tools_file/
#fi


#CONFIG_DEPLOYMENT_RM_USER_DIRS="/opt/qt /usr/share/locale /usr/share/terminfo /usr/share/man /usr/man /usr/arm-linux /usr/lib/pkgconfig /usr/include /usr/icons /usr/local/Trolltech /usr/share/gtk-doc /usr/share/doc /usr/htdocs /usr/manual /usr/info /usr/share/info"
#CONFIG_DEPLOYMENT_RM_USER_FILES="/usr/lib/*.a /usr/lib/libQtTest* /usr/lib/libQt3Support* /usr/lib/libQtSql* /usr/lib/libQtWebKit*"
# ./config/platform/imx/.config

