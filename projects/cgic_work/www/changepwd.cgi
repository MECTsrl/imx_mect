#!/bin/sh

`cat | dos2unix | awk '{if ($0 ~ /Content-Disposition: form-data/) {split($0,a,"="); split(a[2],b,"\""); getline; getline; printf "export %s=%s\n", b[2],$0}}'`

. ./load.cgi

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>$TARGET_NAME REMOTE MANAGEMENT</title>
<link rel="stylesheet" type="text/css" href="style.css">
EOF
if [ -e $PWDFILE ]
then
. $PWDFILE
fi

if [ "$PASSWORD" == "$PWDOLD" ]
then
if [ "$PWDUSER" == "$PWDOLD" ] || [ "$PWDUSER" == "" ]
then
PWDUSER=$PWDNEW
cat <<EOF
</head>
<body>
	<div id="container">
		<div id="header">
			<table width="100%">
				<tr align="left">
					<td>
						<h1><img src="$LOGO_NAME" style="width:240px;height:136px;float=left;vertical-align:middle;">  $TARGET_NAME Password Management</h1>
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
			Service Password Changed!
			</H1>
		</div> <!-- end div content -->
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
cat <<EOF
	</div> <!-- end div container -->
</body>
</html>
EOF
else
if [ "$PWDSUPERUSER" == "$PWDOLD" ] || [ "$PWDSUPERUSER" == "" ]
then
PWDSUPERUSER=$PWDNEW
cat <<EOF
</head>
<body>
	<div id="container">
		<div id="header">
			<table width="100%">
				<tr align="left">
					<td>
						<h1><img src="$LOGO_NAME" style="width:240px;height:136px;float=left;vertical-align:middle;">  $TARGET_NAME Password Management</h1>
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
			Admin Password Changed!
			</H1>
		</div> <!-- end div content -->
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
cat <<EOF
	</div> <!-- end div container -->
</body>
</html>
EOF

else
cat <<EOF
</head>
<body>
		<div id="container">
		<div id="header">
			<table width="100%">
				<tr align="left">
					<td>
						<h1><img src="$LOGO_NAME" style="width:240px;height:136px;float=left;vertical-align:middle;">  $TARGET_NAME Password Management</h1>
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
			<center>
			<H1>
			Wrong Password.
			<H1>
			</center>
		</div> <!-- end div content -->
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
cat <<EOF
	</div> <!-- end div container -->
</body>
</html>
EOF
fi
fi
else
cat <<EOF
</head>
<body>
		<div id="container">
		<div id="header">
			<table width="100%">
				<tr align="left">
					<td>
						<h1><img src="$LOGO_NAME" style="width:240px;height:136px;float=left;vertical-align:middle;">  $TARGET_NAME Password Management</h1>
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
			<center>
			<H1>
			Wrong Password.
			<H1>
			</center>
		</div> <!-- end div content -->
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
cat <<EOF
	</div> <!-- end div container -->
</body>
</html>
EOF

fi
mount -orw,remount /
echo PWDUSER=$PWDUSER > $PWDFILE
echo PWDSUPERUSER=$PWDSUPERUSER >> $PWDFILE
echo PWDADMIN=$PWDADMIN >> $PWDFILE
mount -oro,remount /
