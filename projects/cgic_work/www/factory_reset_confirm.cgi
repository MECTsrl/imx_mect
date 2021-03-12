#!/bin/sh

. ./load.cgi

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>$TARGET_NAME FACTORY RESET</title>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<div id="container">
		<div id="header">
			<table width="100%">
				<tr align="left">
					<td>
						<h1><img src="$LOGO_NAME" style="width:240px;height:136px;float=left;vertical-align:middle;">  $TARGET_NAME Factory Reset</h1>
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
<div id="form">

<form name="myform" enctype="multipart/form-data" action="factory_reset.cgi" method="POST">
<table>
<tr>
<H3>
If you press the reset button you'll reset the system and all data available will be permanently erased.
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
</div> <!-- end div container -->
</body>
</html>
EOF
exit 0
