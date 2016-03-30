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
			<H1>
			Service Password Changed!
			</H1>
		</div> <!-- end div content -->
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
cat <<EOF
EOF
echo "         <div id=\"footer\"><h2>$COMPANY_NAME</h2></div>"
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
			<H1>
			Admin Password Changed!
			</H1>
		</div> <!-- end div content -->
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
cat <<EOF
		<div id="footer"><h2>$COMPANY_NAME</h2></div> 
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
			Wrong Password.
			<H1>
			</center>
		</div> <!-- end div content -->
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
cat <<EOF
		<div id="footer"><h2>$COMPANY_NAME</h2></div> 
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
			Wrong Password.
			<H1>
			</center>
		</div> <!-- end div content -->
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
cat <<EOF
		<div id="footer"><h2>$COMPANY_NAME</h2></div> 
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
