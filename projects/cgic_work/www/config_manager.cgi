#!/bin/sh

# load the configuraation
. ./load.cgi

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>$TARGET_NAME CONFIG MANAGEMENT</title>
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
<h1>$TARGET_NAME CONFIG MANAGEMENT</h1>
</td>
</tr>
</table>

</div>
<div id="content">
<div id="form">

<table style="border:solid 2px #335970;" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >
<tbody>
<form name="sei" method="POST" enctype="multipart/form-data" action="upload.cgi">
	<tr align="right">
		<td>
			Choose splash file (.png):
		</td>
		<td>
			<input type="file" name="SPLASH" required>
		</td>
		<td>
			<input class=bottoni type="submit" value="Update Splash">
		</td>
	</tr>
</form>
</tbody>
</table>
</td>
</tr>
</tbody>
</table>

</div> <!-- end div form -->
<div id="form">

</div> <!-- end div form -->
<BR>
<center>
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
cat <<EOF
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
