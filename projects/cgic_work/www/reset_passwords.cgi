#!/bin/sh

. ./load.cgi

if [ -e $PWDFILE ]
then
	old_dir=`pwd`
	mount -orw,remount /
	echo "PWDUSER=$PWDUSERDEFAULT" > $PWDFILE
	echo "PWDSUPERUSER=$PWDSUPERUSERDEFAULT" >> $PWDFILE
	echo "PWDADMIN=$PWDADMINDEFAULT" >> $PWDFILE
	mount -oro,remount /
	if [ $? == 0 ]
	then
		MSG="All passwords are resetted"
	else
		MSG="Error resetting passwords"
	fi
	cd $old_dir
else
	MSG="Error missing password file"
fi

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>$TARGET_NAME RESET PASSWORDS</title>
<link rel="stylesheet" type="text/css" href="style.css">
EOF
echo "<META http-equiv=\"refresh\" content=\"3;URL=index.cgi\">"
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
			<h1><img src="logo.png" style="width:95px;height:90pxfloat=left;vertical-align:middle;"> $TARGET_NAME RESET PASSWORDS</h1>
</td>
</tr>
</table>
		</div>
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
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='index.cgi'\">"
cat <<EOF
</center>
EOF
echo "         <div id=\"footer\"><h2></h2></div>"
cat <<EOF
	</div> <!-- end div container -->
</body>
</html>
EOF
