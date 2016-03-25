#!/bin/sh

. ./load.cgi

rm -f $SESSIONFILE
PASSWORD=""

cat <<EOF
Content-Type: text/html

<html>
  <head>
    <title>$TARGET_NAME REMOTE MANAGEMENT</title>
    <link rel="stylesheet" type="text/css" href="style.css">
	<META http-equiv="refresh" content="0;URL=index.cgi">
  </head>
  <body>
  </body>
</html>
EOF
