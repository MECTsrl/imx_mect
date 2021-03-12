#!/bin/sh

# Questo e' il file index.cgi, che presenta le impostazioni
# attuali in una pagina HTML e permette di cambiarle

. ./load.cgi

cat <<EOF
Content-Type: text/html

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>$TARGET_NAME Setup</title>
	<link rel="stylesheet" type="text/css" href="style.css">
	<script>
		function date_time(id)
		{
			date = new Date;
			year = date.getFullYear();
			month = date.getMonth();
			month = month +1;
			if(month<10)
			{
				month = "0"+month;
			}
			day = date.getDate();
			if(day<10)
			{
				day = "0"+day;
			}
			hours = date.getHours();
			if(hours<10)
			{
				hours = "0"+hours;
			}
			minutes = date.getMinutes();
			if(minutes<10)
			{
				minutes = "0"+minutes;
			}
			seconds = date.getSeconds();
			if(seconds<10)
			{
				seconds = "0"+seconds;
			}
			result = month+'/'+day+'/'+year+' '+hours+':'+minutes+':'+seconds;

			input.year.value = year;
			input.month.value = month;
			input.day.value = day;
			input.hours.value = hours;
			input.minutes.value = minutes;
			input.seconds.value = seconds;
			setTimeout('date_time("'+id+'");','1000');
			return true;
		}
	</script>
	</head>
	<body>
		<div id="container">
		<div id="header">
			<table width="100%">
				<tr align="left">
					<td>
						<h1><img src="$LOGO_NAME" style="width:240px;height:136px;float=left;vertical-align:middle;">  $TARGET_NAME Configuration</h1>
					</td>
					<td>
EOF
. ./info.cgi
cat <<EOF
					</td>
				</tr>
			</table>
		</div> <!-- end div header -->
		<center>
			<div id="content">
				<div id="form"> 
					<form name="input" action="updatetime.cgi" method="POST">
						<fieldset>
							<legend>System Date and Time</legend>
							<table>
								<tbody>
									<tr>
										<td>
											Year :
										</td>
										<td>
											<input type="text" name="year">
										</td>
									</tr>
									<tr>
										<td>
											Month :
										</td>
										<td>
											<input type="text" name="month">
										</td>
									</tr>
									<tr>
										<td>
											Day :
										</td>
										<td>
											<input type="text" name="day">
										</td>
									</tr>
									<tr>
										<td>
											Hours :
										</td>
										<td>
											<input type="text" name="hours">
										</td>
									</tr>
									<tr>
										<td>
											Minutes :
										</td>
										<td>
											<input type="text" name="minutes">
										</td>
									</tr>
									<tr>
										<td>
											Seconds :
										</td>
										<td>
											<input type="text" name="seconds">
										</td>
									</tr>
									<tr>
										<td colspan="2">
											<hr class="tabhead">
										</td>
									</tr>
									<tr>
										<td>
										
										<input class="bottoni" type="submit" value="Submit">
										</td>
									</tr>
								</tbody>
							</table>
						</fieldset>
					<script type="text/javascript">window.onload = date_time('datetime');</script>
					</form>
				</div>
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
cat <<EOF				
			</div>
			</center>
			</div>
		</div>
	</body>
</html>
EOF
