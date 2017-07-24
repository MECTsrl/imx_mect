# Fix password file permissions.
if test -f "$LUP"; then
    chown root:root "$LUP"
    chmod 0600 "$LUP"
fi

# Any OpenVPN certificate for this device?
test -r "${MNTDIR}/${SN}.ovpn" -a "$(sed -n '/^\s*Subject: .*CN=/ { s/^.*CN=//; s/\/.*//; s/-mect$//; p; }' ${MNTDIR}/${SN}.ovpn)" = "$SN" || do_exit "no OpenVPN certificate for this device." | tee /dev/tty1

# Make sure that OpenVPN configuration directory exists.
if ! test -d "$OVPNCONF"; then
    rm -f "$OVPNCONF"
    mkdir -p "$OVPNCONF"
fi
test -d "$OVPNCONF" || do_exit "no OpenVPN configuration directory." | tee /dev/tty1

# Add/replace the new OpenVPN certificate.
#

# Disable any existing certificates.
find "$OVPNCONF" -type f \( -iname \*.ovpn -o -iname \*.conf \) -exec mv {} {}.$(date '+%F-%T') \;

# Install the new certificate.
install -m 644 "${MNTDIR}/${SN}.ovpn" "${OVPNCONF}/${SN}.ovpn"
test -s "${OVPNCONF}/${SN}.ovpn" || do_exit "cannot install the OpenVPN certificate." | tee /dev/tty1

# Change the default (development) root password.
sed -i 's:^root\:[^\:]\+\::root\:$1$5FNVDbNV$Qkv/sIFbIQwuZdbz6rdIs0\::' "$SHADOWFILE"

# Make sure that the cron tab is set for periodic log upload.
test -s "$CRONTAB" || touch "$CRONTAB"
# Uncomment the sync schedule in cron tab, if commented.
sed -i "/ $(echo $LUS | sed 's|/|\\/|g')"'\s*$/ { s/^[ 	#]*//; s/\s*$//; }' "$CRONTAB"
# Still no sync schedule?  Add it!
if ! grep -q " $LUS\\s*\$" "$CRONTAB"; then
    sed -n "/ $(echo $LUS | sed 's|/|\\/|g')"'\s*$/ { s/^[ 	#]*//; s/\s*$//; p; }' "${CRONTAB}.default" >> "$CRONTAB"
    # Still no schedule by now?  That's very weird...
    grep -q "$LUS\\s*\$" "$CRONTAB" || do_exit "cron tab setup failed." | tee /dev/tty1
fi

# Activate the configuration changes.
"$OVPNRC" stop; sleep 1; "$OVPNRC" start
"$CRONRC" stop; sleep 1; "$CRONRC" start

# All set.
( echo -e "\r"; echo -e "Device update for MECT Remote Services succeeded.\r" ) | tee /dev/tty1
do_exit
