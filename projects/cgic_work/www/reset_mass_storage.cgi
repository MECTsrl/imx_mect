#!/bin/sh

. ./load.cgi

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>$TARGET_NAME RESET SDCARD</title>
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
<h1>$TARGET_NAME RESET SDCARD</h1>
</td>
</tr>
</table>
</div>
<div id="content">
<center>
<div id="form">

<form name="myform" enctype="multipart/form-data" action="formatsdcard.cgi" method="POST">
<table>
<tr>
<H3>
If you press the reset button you'll reset the SDcard and all data avaialable on your SDcard will be permanently erased.
</H3>
</tr>
<BR>
<tr>
<input class=bottoni type="submit" value="Reset">
</tr>
</table>
</div> <!-- end div form -->
<BR>
<form>
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
cat <<EOF
 <input class=bottoni type="button" value="Back" onclick="window.location.href='menu.cgi'">
</form>
</center>
</div> <!-- end div content -->
EOF
echo "         <div id=\"footer\"><h2>$COMPANY_NAME</h2></div>"
cat <<EOF
</div> <!-- end div container -->
</body>
</html>
EOF
exit 0
