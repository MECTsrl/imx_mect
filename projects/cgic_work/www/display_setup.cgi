#!/bin/sh

COMMAND=`cat`

. ./load.cgi

eval $COMMAND

if [ "$BRIGHTNESS" != "" ]
then
	SCALED_BRIGHTNESS=`expr $BRIGHTNESS \* 50 / 100 + 20`
	echo $SCALED_BRIGHTNESS > /sys/devices/platform/mxs-bl.0/backlight/mxs-bl/brightness
	echo "echo $SCALED_BRIGHTNESS > /sys/devices/platform/mxs-bl.0/backlight/mxs-bl/brightness" > $LOCAL_ETC_DIR/brightness
	MSG="Brightness level set to $BRIGHTNESS"
fi

if [ "$SCREENSAVER" != "" ]
then
	if [ `grep ScreenSaverSec: $LOCAL_ETC_DIR/atn01.conf` ]
	then
		awk '{if ($0 ~/ScreenSaverSec:/) {print ScreenSaverSec: '$SCREENSAVER'} else {print $0}}' $LOCAL_ETC_DIR/atn01.conf > /tmp/atn01.conf
		mv /tmp/atn01.conf $LOCAL_ETC_DIR/atn01.conf
	else
		echo "ScreenSaverSec: $SCREENSAVER" >> $LOCAL_ETC_DIR/atn01.conf
	fi
	MSG="Screen saver timeout set to $SCREENSAVER"
fi

if [ "$TSCALIB" != "" ]
then
	/etc/rc.d/init.d/autoexec stop > /dev/null 2>&1
	rm -f $LOCAL_ETC_DIR/pointercal
	/etc/rc.d/init.d/autoexec start > /dev/null 2>&1
	MSG="Reset the touch calibration file."
fi

if [ $? == 0 ]
then
	TABLE="<table style=\"border:solid 2px #335970;\" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >"
else
	TABLE="<table style=\"border:solid 2px #FF0000;\" bgcolor=#fffbff cellspacing=10 cellpadding=4 align=center >"
	MSG="Problem to update display settings"
fi

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>LAN SETUP</title>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<div id="container">
<div id="header">
<table width="100%">
<tr align="right">
<td>
EOF
. ./info.cgi
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
EOF
echo $TABLE
cat <<EOF
<tbody>
<tr>
<td>
EOF
echo "$MSG"
cat <<EOF
</td>
</tr>
</tbody>
</table>
</div>                                                                                
EOF
echo "<input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
echo "<input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='display.cgi'\">"
cat <<EOF
</center>
</div>                                                                                
EOF
echo "         <div id=\"footer\"><h2>$COMPANY_NAME</h2></div>"
cat <<EOF
</body>
</html>
EOF