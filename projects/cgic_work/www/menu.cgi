#!/bin/sh

# manage the session expire
if [ -e "/tmp/.session" ]
then
	. /tmp/.session
	if [ "$SESSION_NB" == "" ]
	then
		echo   "SESSION_NB=`grep GET /var/log/boa/access_log | grep -c '"-"'`" >> /tmp/.session
		. /tmp/.session
	fi
	if [ "$SESSION_NB" != "`grep GET /var/log/boa/access_log | grep -c '"-"'`" ]
	then 
		rm -f /tmp/.session
	fi
fi

. ./load.cgi

if [ ! -e $SESSIONFILE ] || [ "$PASSWORD" == "" ]
then
cat <<EOF
Content-Type: text/html

<html>
<head>
<title>$TARGET_NAME ERROR</title>
<link rel="stylesheet" type="text/css" href="style.css">
EOF
echo "<META http-equiv=\"refresh\" content=\"3;URL=index.cgi\">"
cat <<EOF
<META http-equiv="refresh" content="3;URL=index.cgi">
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
<h1>$TARGET_NAME REMOTE MANAGEMENT</h1>
</td>
</tr>
</table>
		</div>
		<div id="content">
			<center>
			<H1>
			session expired!
EOF
			echo $SESSION_NB != "`grep GET /var/log/boa/access_log | grep -c '"-"'`"
cat <<EOF
			<H1>
			</center>
		</div> <!-- end div content -->
<BR>
<center>
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='index.cgi'\">"
cat <<EOF
</center>
EOF
echo "         <div id=\"footer\"><h2>$COMPANY_NAME</h2></div>"
cat <<EOF
	</div> <!-- end div container -->
</body>
</html>
EOF
		echo "SESSION_NB=`grep GET /var/log/boa/access_log | grep -c '"-"'`" >> /tmp/.session
fi

# load the configuraation
. ./load.cgi

# start a new session
echo "SESSION_NB=`grep GET /var/log/boa/access_log | grep -c '"-"'`" >> $SESSIONFILE

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>$TARGET_NAME REMOTE MANAGEMENT</title>
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
<h1>$TARGET_NAME REMOTE MANAGEMENT</h1>
</td>
</tr>
</table>
</div>
<div id="content">
<div id="form">

<table style="border:solid 2px #335970;" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >
<tbody>
		<tr>
			<td>
					<input class=bottoni type="button" value="LAN config" onclick="window.location.href='lan_config.cgi'">
			</td>
			<td>
					<input class=bottoni type="button" value="Date and time" onclick="window.location.href='date_time.cgi'">
			</td>
			<td>
					<input class=bottoni type="button" value="Display settings" onclick="window.location.href='display.cgi'">
			</td>
			<td>
					<input class=bottoni type="button" value="Manage Configuration" onclick="window.location.href='config_manager.cgi'">
			</td>
		</tr>
</tbody>
</table>
<BR>
<BR>
<table style="border:solid 2px #335970;" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >
<tbody>
		<tr>
			<td>
					<input class=bottoni type="button" value="Alarms" onclick="window.location.href='alarms_manager.cgi'">
			</td>
			<td>
					<input class=bottoni type="button" value="Logs" onclick="window.location.href='logs_manager.cgi'">
			</td>
			<td>
					<input class=bottoni type="button" value="Trend" onclick="window.location.href='trend_manager.cgi'">
			</td>
			<td>
					<input class=bottoni type="button" value="Recipes" onclick="window.location.href='recipes_manager.cgi'">
			</td>
		</tr>
</tbody>
</table>
<BR>
<BR>
<table style="border:solid 2px #335970;" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >
<tbody>
		<tr>
			<td>
					<input class=bottoni type="button" value="Manage password" onclick="window.location.href='managepwd.cgi'">
			</td>
EOF
if [ "$PASSWORD" != "" ] && [ "$PASSWORD" = "$PWDSUPERUSER" -o "$PASSWORD" = "$PWDADMIN" ]
then
cat <<EOF
			<td>
					<input class=bottoni type="button" value="Update firmware" onclick="window.location.href='upgrade.cgi'">
			</td>
EOF
fi
cat <<EOF
		</tr>
</tbody>
</table>
EOF
if [ "$PASSWORD" != "" ] && [ "$PASSWORD" = "$PWDADMIN" ]
then
cat <<EOF
<BR>
<BR>
<table style="border:solid 2px #335970;" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >
<tbody>
		<tr>
			<td>
					<input class=bottoni type="button" value="Reset passwords" onclick="window.location.href='reset_passwords.cgi'">
			</td>
		</tr>
</tbody>
</table>
EOF
fi
cat <<EOF
<BR>
<BR>
<table style="border:solid 2px #335970;" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >
<tbody>
		<tr>
			<td>
					<input class=bottoni type="button" value="Logout" onclick="window.location.href='logout.cgi'">
			</td>
		</tr>
</tbody>
</table>

</div> <!-- end div form -->
</div> <!-- end div content -->
EOF
echo "         <div id=\"footer\"><h2>$COMPANY_NAME</h2></div>"
cat <<EOF
</div> <!-- end div container -->
</body>
</html>

EOF
exit 0
