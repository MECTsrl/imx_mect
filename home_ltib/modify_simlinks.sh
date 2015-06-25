#/bin/bash

if [ -d rootfs_nolink ]; then 

	cd rootfs_nolink/usr/lib
	 
	echo "Removing simlinks in `pwd` "
	for f in $(find . -maxdepth 1 -type l)
	do
	    sudo cp --remove-destination $(readlink $f) $f > /dev/null 2>&1
	done

	cd - > /dev/null 2>&1

	cd rootfs_nolink/lib

	echo "Removing simlinks in `pwd` "
	for f in $(find . -maxdepth 1 -type l)
	do
	   sudo cp --remove-destination $(readlink $f) $f > /dev/null 2>&1
	done

	cd - > /dev/null 2>&1

	echo "Cleaning simlinks done"
else
	echo "Create a copy of the current rootfs under rootfs_nolink directory. Then re-run this script"
fi
