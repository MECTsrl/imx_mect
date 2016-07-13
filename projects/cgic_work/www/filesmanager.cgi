#!/bin/sh

DATA=`cat`

. ./load.cgi

ERROR=0

for x in `echo $DATA | tr "&" "\n"`; do
   if [ "$x" != "delete=Delete" ] && [ "$x" != "download=Download" ] && [ ! `echo $x | grep ROOT_DIR` ]
   then
   	  FULLPATHFILE=`echo $x | cut -d= -f2 | sed s/'%2F'/'\/'/g`
	  FILE=`basename $FULLPATHFILE`
   	  DIRECTORY=`dirname $FULLPATHFILE`
   	  FILESTOACTION="$FILESTOACTION $FILE "
	  if [ "$DIRECTORY" == "$BASE_DIR/$ALARMS_DIR" ]
	  then
		$SIGN $FULLPATHFILE | cut -d\  -f1 > $FULLPATHFILE.sign
		ERROR=$?
		if [ "$ERROR" != "0" ]
		then
			break;
		fi
		FILESTOACTION="$FILESTOACTION $FILE.sign"
	  fi
   else 
   	if [ `echo $x | grep ROOT_DIR` ]
	then
		ROOT_DIR=`echo $x | cut -d= -f2 | sed s/'%2F'/'\/'/g`
	fi
   fi
done

# trim the initial and final spaces
FILESTOACTION=`echo $FILESTOACTION`

if [ "`echo $DATA | grep -c delete`" == "1" ]
then
   ACTION="delete"
else
   ACTION="download"
fi

# nothing to do
if [ "$FILESTOACTION" == "" ]
then
cat <<EOF
Content-Type: text/html

<html>
<head>
<title> REMOTE UPDATER </title>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<div id="container">
<div id="header">
<table width="100%">
<tr align="right">
<td>
EOF
. $OLD_DIR/info.cgi
cat <<EOF
</td>
</tr>
<tr>
<td>
<h1>REMOTE UPDATER</h1>
</td>
</tr>
</table>
</div>
<center>
<div id="content">
<table style="border:solid 2px #335970;" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >
<tbody>
<tr>
<td>
    nothing to $ACTION
</td>
</tr>
</tbody>
</table>
</div>                                                                                
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
echo "      <input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='filebrowser.cgi?ROOT_DIR=$ROOT_DIR'\">"
cat <<EOF
</center>
</div>                                                                                
EOF
echo "         <div id=\"footer\"><h2>$COMPANY_NAME</h2></div>"
cat <<EOF
</body>
</html>
EOF
exit 0
fi

# go into the files directory
OLD_DIR=`pwd`
cd $DIRECTORY

if [ "$ERROR" == "0" ]
then
# crea zip file
if [ "$ACTION" != "delete" ]
then
   # zip log file
   if [ "`echo $FILESTOACTION | wc -w`" == "1" ]
   then
      zipfilename=$FILESTOACTION.zip
   else
      zipfilename=`date '+%Y_%m_%d'`_`date '+%H%M%S'`.zip
   fi
   /usr/bin/zip -q -r $zipfilename $FILESTOACTION
   ERROR=$?
fi
fi

# clean the sign file
for x in $FILESTOACTION; do
	if [ `echo $x | grep .sign$` ]
	then
		rm -f $x
	fi
done

if [ "$ERROR" == "0" ]
then
# download
if [ "$ACTION" == "download" ]
then
cat <<EOF
Content-type: multipart/x-zip
Content-disposition: attachment; filename="$zipfilename"

EOF
	cat $zipfilename
	rm -f $zipfilename
else
# delete
	rm -rf $FILESTOACTION
cat <<EOF
Content-Type: text/html

<html>
<head>
<title> REMOTE UPDATER </title>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<div id="container">
<div id="header">
<table width="100%">
<tr align="right">
<td>
EOF
. $OLD_DIR/info.cgi
cat <<EOF
</td>
</tr>
<tr>
<td>
<h1>REMOTE UPDATER</h1>
</td>
</tr>
</table>
</div>
<center>
<div id="content">
<table style="border:solid 2px #335970;" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >
<tbody>
<tr>
<td>
    Success to $ACTION $FILESTOACTION $ROOT_DIR.
</td>
</tr>
</tbody>
</table>
</div>                                                                                
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
echo "      <input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='filebrowser.cgi?ROOT_DIR=$ROOT_DIR'\">"
cat <<EOF
</center>
</div>                                                                                
EOF
echo "         <div id=\"footer\"><h2>$COMPANY_NAME</h2></div>"
cat <<EOF
</body>
</html>

EOF
fi
else
cat <<EOF
Content-Type: text/html


<html>
<head>
<title> REMOTE UPDATER </title>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<div id="container">
<div id="header">
<table width="100%">
<tr align="right">
<td>
EOF
. $OLD_DIR/info.cgi
cat <<EOF
</td>
</tr>
<tr>
<td>
<h1>REMOTE UPDATER</h1>
</td>
</tr>
</table>
</div>
<center>
<div id="content">

<table style="border:solid 2px #FF0000;" bgcolor=#fffbff cellspacing=10 cellpadding=4 align=center >
<tbody>
<tr>
<td>
    Fail to $ACTION $FILESTOACTION.
</td>
</tr>
</tbody>
</table>
</div>
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
cat <<EOF
      <input class=bottoni type="button" value="Back" onclick="window.location.href='menu.cgi'">
</center>
</div>                                                                                
EOF
echo "         <div id=\"footer\"><h2>$COMPANY_NAME</h2></div>"
cat <<EOF
</body>
</html>

EOF
fi

cd $OLD_DIR
