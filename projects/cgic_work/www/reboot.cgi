#!/bin/sh

. ./load.cgi

eval $QUERY_STRING

if [ "$COMMAND" == "RESTART" ]
then
	MSG="Restarting the application..."
	TIMEOUT=5
	NEXTPAGE="menu.cgi"
else
	if [ "$COMMAND" == "REBOOT" ]
	then
		MSG="Rebooting the system..."
		TIMEOUT=20
		NEXTPAGE="${IPADDR}/index.cgi"
	else
		MSG="Invalid command."
		TIMEOUT=2
		NEXTPAGE="menu.cgi"
	fi
fi

cat <<EOM
Content-Type: text/html

<html>
	<head>
EOM
	echo "<meta http-equiv=\"refresh\" content=\"$TIMEOUT;url=http://$NEXTPAGE\">"
cat <<EOM
	<title>$TARGET_NAME REMOTE MANAGEMENT</title>
	<link rel="stylesheet" type="text/css" href="style.css">
	</head>
	<body>
		<div id="container">
			<div id="header">
<table width="100%">
<tr align="right">
<td>
EOM
. ./info.cgi
cat <<EOM
</td>
</tr>
<tr>
<td>
				<h1><img src="logo.png" style="width:95px;height:90pxfloat=left;vertical-align:middle;"> $TARGET_NAME REMOTE MANAGEMENT</h1>
</td>
</tr>
</table>
			</div>
			<center>
EOM
echo "      <H1>$MSG</H1>"
cat <<EOM
			</center>
		</div>
		<div id="footer"><h2></h2></div> 
	</body>
</html>
EOM

if [ "$COMMAND" == "RESTART" ]
then
	/etc/rc.d/init.d/autoexec stop >/dev/null 2>&1
	/etc/rc.d/init.d/autoexec start >/dev/null 2>&1
else
	if [ "$COMMAND" == "REBOOT" ]
	then
		/sbin/reboot
	fi
fi

