#!/bin/sh

. ./load.cgi

`cat | dos2unix | awk '{if ($0 ~ /Content-Disposition: form-data/) {split($0,a,"="); split(a[2],b,"\""); getline; getline; printf "export %s=%s\n", b[2],$0}}'`

if [ -e $PWDFILE ]
then
. $PWDFILE
fi

LEVEL="None"
if [ $PWDUSER != "" ] && [ "$PWDUSER" = "$PASSWORD" ]
then
	LEVEL="User"
fi
if [ $PWDSUPERUSER != "" ] && [ "$PWDSUPERUSER" = "$PASSWORD" ]
then
	LEVEL="Super User"
fi
if [ $PWDADMIN != "" ] && [ "$PWDADMIN" = "$PASSWORD" ]
then
	LEVEL="Administrator"
fi

if [ "$LEVEL" != "None" ]
then
	echo "PASSWORD=$PASSWORD" > $SESSIONFILE
	DEST_PAGE=$HOME_PAGE
else
	DEST_PAGE="index.cgi"
fi

source $DEST_PAGE
