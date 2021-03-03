#!/bin/sh

if [ -e "/tmp/.session" ]
then
	rm -f /tmp/.session
fi

. ./load.cgi

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
        <h1><img src="logo.png" style="width:95px;height:90pxfloat=left;vertical-align:middle;"> $TARGET_NAME REMOTE MANAGEMENT</h1>
</td>
</tr>
</table>
      </div>
      <div id="content">
        <center>
          <div id="form">
            <form name="myform" enctype="multipart/form-data" action="checkpwd.cgi" method="POST">
              Enter Password:
              <input type="password" size="25" name="PASSWORD">
              <input class=bottoni type="submit" value="Login" onClick>
            </form>
          </div>
        </center>
      </div>
EOF
echo "         <div id=\"footer\"><h2></h2></div>"
cat <<EOF
</body>
</html>
EOF
