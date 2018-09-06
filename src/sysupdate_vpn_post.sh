
# Add/replace new OpenVPN certificates.
#

# Any certificates for this device?
ls "${MNTDIR}/${SN}"*".ovpn" 2>/dev/null | grep -q . || do_exit "no certificate for this device."

# Make sure that OpenVPN configuration directory exists.
if ! test -d "$OVPNCONF"; then
    rm -f "$OVPNCONF"
    mkdir -p "$OVPNCONF"
fi
test -d "$OVPNCONF" || do_exit "no OpenVPN configuration directory." | tee /dev/tty1

# Disable any existing certificates.
find "$OVPNCONF" -type f \( -iname \*.ovpn -o -iname \*.conf \) -exec mv {} {}.$(date '+%F-%T') \;

# Install the new certificate.
ls "${MNTDIR}/${SN}"*".ovpn" 2>/dev/null | while read c; do
    install -m 644 "$c" "${OVPNCONF}/$(basename $c)"
    test -s "${OVPNCONF}/$(basename $c)" || do_exit "cannot install $(basename $c) certificate." | tee /dev/tty1
done

# Change the default (development) root password.
#

# Change root password.
sed -i 's:^root\:[^\:]\+\::root\:$1$5FNVDbNV$Qkv/sIFbIQwuZdbz6rdIs0\::' "$SHADOWFILE"

# Activate configuration changes.
"$OVPNRC" stop; sleep 1; "$OVPNRC" start

# All set.
( echo -e "\r"; echo -e "Device update for MECT Remote Services succeeded.\r" ) | tee /dev/tty1
do_exit
