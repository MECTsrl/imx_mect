#!/bin/sh


mntdir=/local/sd_card
mntpoint=`df | cut -d" " -f1 | grep mmc`

if [ -n "$mntpoint" ]; then
	/etc/rc.d/init.d/autoexec stop > /dev/null 2>&1
	if [ -x /usr/bin/splash ]
	then
		/usr/bin/splash --text "Resetting SD card ..." --dimension 42 -qws > /dev/null 2>&1 &
	fi
	if /bin/umount $mntdir 2>/dev/null; then
		/sbin/mkfs.vfat $mntpoint
		if [ $? == 0 ]; then
			MSG="The SD CARD has been resetted. System needs a Reboot"
		else
			MSG="Error resetting SD CARD"
		fi
	else
		MSG="Error resetting SD CARD"

	fi
	if [ -x /usr/bin/splash ]
	then
		killall splash
	fi
	/etc/rc.d/init.d/autoexec start > /dev/null 2>&1
else
	MSG="SD Card not avaialable on your system"
fi

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>$TARGET_NAME Format SDcard</title>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
	<div id="container">
		<div id="header">
			<table width="100%">
				<tr align="left">
					<td>
						<h1><img src="$LOGO_NAME" style="width:auto;height:136px;float=left;vertical-align:middle;">  $TARGET_NAME Format SDcard</h1>
					</td>
					<td>
EOF
. ./info.cgi
cat <<EOF
					</td>
				</tr>
			</table>
		</div> <!-- end div header -->
		<div id="content">
			<H1>
EOF
echo $MSG
cat <<EOF
			</H1>
		</div> <!-- end div content -->
<BR>
<center>
EOF
        echo "<input class=bottoni type=\"button\" value=\"Reboot\" onclick=\"window.location.href='reboot.cgi?COMMAND=REBOOT'\">"

cat <<EOF
</center>
	</div> <!-- end div container -->
</body>
</html>
EOF
