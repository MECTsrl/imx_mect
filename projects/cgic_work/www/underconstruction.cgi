#!/bin/sh

. ./load.cgi

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>$TARGET_NAME ERROR</title>
<link rel="stylesheet" type="text/css" href="style.css">
EOF
echo "<META http-equiv=\"refresh\" content=\"3;URL=$HOME_PAGE\">"
cat <<EOF
<META http-equiv="refresh" content="3;URL=index.cgi">
</head>
<body>
	<div id="container">
		<div id="header">
			<h1>$TARGET_NAME REMOTE MANAGEMENT</h1>
		</div>
		<div id="content">
			<center>
			<H1>
			Option not yet available.
			<H1>
			</center>
		</div> <!-- end div content -->
EOF
cat <<EOF
<BR>
<center>
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
cat <<EOF
</center>
EOF
echo "         <div id=\"footer\"><h2>$COMPANY_NAME</h2></div>"
cat <<EOF
	</div> <!-- end div container -->
</body>
</html>
EOF
