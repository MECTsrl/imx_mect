
cd "$CWD"

if test -r "${SN}.ovpn"; then
    # Add/replace OpenVPN certificate.
    if ! test -d "$OVPNCONF"; then
	rm -f "$OVPNCONF"
	mkdir -p "$OVPNCONF"
    fi

    if test -d "$OVPNCONF"; then
	cp "${SN}.ovpn" "${OVPNCONF}/${SN}.ovpn"
	test -s "${OVPNCONF}/${SN}.ovpn" || echo "cannot install the OpenVPN certificate." | tee /dev/tty1
    else
	echo "no OpenVPN configuration directory." | tee /dev/tty1
    fi
else
    echo "no OpenVPN certificate for this device." | tee /dev/tty1
fi

# Make sure that the cron tab is set for periodic log upload.
test -s "$CRONTAB" || touch "$CRONTAB"

# Uncomment the sync schedule, if present.
sed -i "/ $(echo $LUS | sed 's|/|\\/|g')"'\s*$/ { s/^[ 	#]*//; s/\s*$//; }' "$CRONTAB"

# Still no schedule, add it.
if ! grep -q " $LUS\\s*\$" "$CRONTAB"; then
    sed -n "/ $(echo $LUS | sed 's|/|\\/|g')"'\s*$/ { s/^[ 	#]*//; s/\s*$//; p; }' "${CRONTAB}.default" >> "$CRONTAB"

    # No schedule yet?  Stop with error.
    grep -q "$LUS\\s*\$" "$CRONTAB" || echo "cron tab setup failed." | tee /dev/tty1
fi

# Activate configuration changes.
"$OVPNRC" stop; sleep 1; "$OVPNRC" start
"$CRONRC" stop; sleep 1; "$CRONRC" start

# Exit
( echo ""; echo "Device update for MECT Remote Services succeeded." ) | tee /dev/tty1
do_exit
