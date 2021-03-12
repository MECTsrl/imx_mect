#!/bin/sh

# load the configuraation
. ./load.cgi

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>$TARGET_NAME ALARMS MANAGEMENT</title>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<div id="container">
		<div id="header">
			<table width="100%">
				<tr align="left">
					<td>
						<h1><img src="$LOGO_NAME" style="width:240px;height:136px;float=left;vertical-align:middle;">  $TARGET_NAME REMOTE MANAGEMENT</h1>
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
<div id="form">

<form name="tre" method="POST" enctype="multipart/form-data" action="upload.cgi">
<table style="border:solid 2px #335970;" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >
<tbody>
		</tr>
			<td>
			</td>
			<td>
EOF
echo "<input class=bottoni type=\"button\" value=\"Manage alarms\" onclick=\"window.location.href='filebrowser.cgi?ROOT_DIR=$ALARMS_DIR'\">";
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
</div> <!-- end div container -->
</body>
</html>

EOF
exit 0
