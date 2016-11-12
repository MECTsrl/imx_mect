#!/bin/sh

#set -x

# Do not change anything on normal root.
test -z "$RPM_BUILD_ROOT" -o "$RPM_BUILD_ROOT" = '/' && exit 0

STRIP=${1:-strip}
PATH=$SPOOF_PATH

# Strip all ELF binaries.
for f in `find "$RPM_BUILD_ROOT" -type f \( -perm -0100 -or -perm -0010 -or -perm -0001 \) -exec file {} \; | \
        grep -v "^${RPM_BUILD_ROOT}/\?usr/lib/debug"  | \
	sed -n -e 's/^\(.*\):[ 	]*ELF.*, not stripped/\1/p'`
do
	$STRIP --strip-all "$f" || :
done
