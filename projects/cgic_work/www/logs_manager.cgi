#!/bin/sh

# load the configuraation
. ./load.cgi

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>$TARGET_NAME LOGS MANAGEMENT</title>
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
<h1><img src="logo.png" style="width:95px;height:90pxfloat=left;vertical-align:middle;">  $TARGET_NAME LOGS MANAGEMENT</h1>
</td>
</tr>
</table>
</div>
<div id="content">
<div id="form">

<form name="tre" method="POST" enctype="multipart/form-data" action="upload.cgi">
<table style="border:solid 2px #335970;" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >
<tbody>
	<tr>
		<td>
			<input type="file" name="LOGSTBL" required>
		</td>
		<td>
			<input class=bottoni type="submit" value="Update Partial logs">
		</td>
	</tr>
		</tr>
			<td>
			</td>
			<td>
EOF
echo "<input class=bottoni type=\"button\" value=\"Manage logs\" onclick=\"window.location.href='logs_filter.cgi'\">";
cat <<EOF
			</td>
		</tr>

</tbody>
</table>
</form>
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
echo "         <div id=\"footer\"><h2></h2></div>"
cat <<EOF
</div> <!-- end div container -->
</body>
</html>

EOF
exit 0
