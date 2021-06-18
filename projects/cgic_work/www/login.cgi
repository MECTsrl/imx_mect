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
    <title>$TARGET_NAME Remote Management</title>
    <link rel="stylesheet" type="text/css" href="style.css">
  </head>
  <body>
    <div id="container">
		<div id="header">
			<table width="100%">
				<tr align="left">
					<td>
						<h1><img src="$LOGO_NAME" style="width:auto;height:136px;float=left;vertical-align:middle;">  $TARGET_NAME Remote Management</h1>
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
            <form name="myform" enctype="multipart/form-data" action="checkpwd.cgi" method="POST">
              Enter Password:
              <input type="password" size="25" name="PASSWORD">
              <input class=bottoni type="submit" value="Login" onClick>
            </form>
          </div>
        </center>
      </div>
</body>
</html>
EOF
