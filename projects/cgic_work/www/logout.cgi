#!/bin/sh

. ./load.cgi

rm -f $SESSIONFILE
PASSWORD=""

cat <<EOF
Content-Type: text/html

<html>
  <head>
    <title><img src="logo.png" style="width:95px;height:90pxfloat=left;vertical-align:middle;"> $TARGET_NAME REMOTE MANAGEMENT</title>
    <link rel="stylesheet" type="text/css" href="style.css">
	<META http-equiv="refresh" content="0;URL=index.cgi">
  </head>
  <body>
  </body>
</html>
EOF
