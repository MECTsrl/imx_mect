#!/bin/sh

ppp=ppp0
pidfile=/var/run/$ppp.pid
peersdir=/etc/ppp/peers
peerfile=usb3g
chatdir=/etc/ppp
chatfile=chat-usb3g
resolv_file=/etc/resolv.conf
options="holdoff 15 persist maxfail 0"

NETCONFIG=/local/etc/sysconfig/net.conf

INIT_NETWORK=/etc/rc.d/init.d/network


clear_defroutes_resolv()
{
    for r in "" `/sbin/route -n | /usr/bin/awk '/^0\.0\.0\.0/ { print $2; }'`; do
        test -z "$r" && continue

        /sbin/route delete default gw "$r"
    done

    echo "" > $resolv_file
}

# Expects: <dial#> <APN>
setup()
{
    test $# -ne 2 && return 1

    dn="$1"
    apn="$2"

    /bin/sed -i "s/^OK 'AT+CGDCONT=1,\"IP\",\".*/OK 'AT+CGDCONT=1,\"IP\",\"$apn\"'/" $chatdir/$chatfile
    /bin/sed -i "s/^OK 'ATD.*/OK 'ATD$dn'/" $chatdir/$chatfile
}

start()
{
    test -r $pidfile && test -d /proc/$(/bin/cat $pidfile) && return 0

    test -f $peersdir/$peerfile || return 1

    test -r "$NETCONFIG" || return 1
    source "$NETCONFIG"

    test "$ONBOOTP0" = "1" || return 0

    # DNS setup: automatic or static.
    #

    if test -z "$NAMESERVERP01" -a -z "$NAMESERVERP02"; then
        options="$options usepeerdns"
    else
        echo "# Created by $0. Do not edit." > $resolv_file

        if test -n "$NAMESERVERP01"; then
            /bin/grep "nameserver\s\+$NAMESERVERP01" $resolv_file || echo "nameserver $NAMESERVERP01" >> $resolv_file
        fi

        if test -n "$NAMESERVERP02"; then
            /bin/grep "nameserver\s\+$NAMESERVERP02" $resolv_file || echo "nameserver $NAMESERVERW02" >> $resolv_file
        fi
    fi

    # Default gateway setup: automatic or unchanged.
    #

    if test -z "$GATEWAYP0"; then
        for r in "" $(/sbin/route -n | /usr/bin/awk '/^0\.0\.0\.0/ { print $2; }'); do
            test -z "$r" && continue

            /sbin/route delete default gw "$r"
        done

        options="$options defaultroute"
    fi

    options="$options user \"$USERP0\" password \"$PASSWORDP0\""

    eval /sbin/pppd call $peerfile $options
}

stop()
{
    if test -r $pidfile; then
        pid=$(/bin/cat $pidfile)
        test -n "$pid" || return 1

        if test -d /proc/$pid; then
            kill $pid

            for t in $(seq 1 1 10); do
                sleep 1

                test -d /proc/$pid || break
            done
            test -d /proc/$pid && return 1

            if test -r "$NETCONFIG"; then
                source "$NETCONFIG"

                if test -n "$GATEWAY0"; then
                    clear_defroutes_resolv

                    test -x $INIT_NETWORK && $INIT_NETWORK restart
                fi
            fi
        fi
    else
	# TODO may terminate unrelated PPP links.
        killall pppd
    fi

    return 0
}

action="$1"
shift

case "$action" in
    "setup")
        setup "$@"
    ;;

    "start")
        start
    ;;

    "stop")
        stop
    ;;

    *)
        echo "Usage: $(basename $0) <start|stop|setup>" >&2

        exit 1
    ;;
esac
