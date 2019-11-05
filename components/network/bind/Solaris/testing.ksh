#!/bin/ksh
#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2019, Oracle and/or its affiliates. All rights reserved.
#

function usage
{
    # Display usage
    print "
usage ${I##*/} -d directory -p PROTO_DIR
        [-X] [-b bind-port] [-r rndc-port]

Creates a simple named(8) configuration and tests some features.
Ideally this will be expanded over time.

Written for use by Userland's tested-and-compared feature.

Required Options:
    -d directory    Path where BIND files will be read/written.
    -p directory    Root of command path i.e. '/' or $PROTO_DIR

Optional options:
    -b bind-port    Port named will listen on for requests. [$bind_port_d]
    -r rndc_port    Port named will listen on for control [$rndc_port_d]
    -X              Debug
    -?              Display this usage
"
}

function newdir
{
    # Create a new directory if it does not already exist.
    # Exits shell on error.
    typeset directory=$1
    if [[ ! -d $directory ]]; then
	mkdir -p $directory || ret=$?
	if [[ $ret -ne 0 ]]; then
	    print -u2 \
		  "Failed to create configuration directory: $directory: $ret"
	    exit $ret
	fi
    fi
}
function e
{
    # e is for error. print to FD2 (standard error).
    print -u2 $@
}
function d
{
    # d is for display.
    print $@
}

function run
{
    # Display command, execute it and display exit code.
    if [[ $1 == "-e" ]]; then
	exp=$2
	shift 2
    fi
    typeset cmd=$1
    typeset -i ret=0
    shift
    d "RUNNING: $cmd $@"
    $cmd $@ || ret=$?
    if (( ret != exp )); then
	e "RESULT: $ret (UNEXPECTED)"
    else
	d "RESULT: $ret"
    fi
    d '====================================================================='
    return $ret
}

# Main procedure.
typeset -r I=${0}
integer bind_port_d=5353
integer rndc_port_d=8953
integer bind_port=$bind_port_d
integer rndc_port=$rndc_port_d
integer fail

# Read command line arguments.
while getopts :b:d:p:r:r:X opt; do
    case $opt in
	(b) bind_port=$OPTARG;;
	(d) directory=$OPTARG;;
	(p) PROTO=$OPTARG;;
	(r) rndc_port=$OPTARG;;
	(X) set -x; typeset -ft $(typeset +f);;
	(?) usage; exit 0;;
    esac
done
shift `expr $OPTIND - 1`	# Skip over option arguments

if [[ -z $directory || -z $PROTO ]]; then
    usage; exit 2
fi

ret=0
# Create directories as needed.
newdir $directory
if [[ ! -f $runlog ]]; then
    dir=${runlog%/*}
    if [[ -n $dir && ! -d $dir ]]; then
	newdir $dir
    fi
fi

# Set command paths from provided PROTO.
SBIN=${PROTO%*/}/usr/sbin
BIN=${PROTO%*/}/usr/bin

# Check commands are present.  Could read this list from the package
# file, but for now just looks for those that are used here.
for command in $SBIN/named $BIN/dig $SBIN/named-checkconf; do
    if [[ ! -x $command ]]; then
	e "$command missing!"
	(( fail++ ))
    fi
done
(( fail > 0 )) && exit $fail

# set LD_LIBRARY_PATH only when PROTO is not root, and not already set.
if [[ ${PROTO} != '/' && -z $LD_LIBRARY_PATH ]]; then
    if [[ -d ${PROTO}/usr/lib/dns ]]; then
	export LD_LIBRARY_PATH=${PROTO}/usr/lib/dns
    else
	e "Warning: Library directory not found: ${PROTO}/usr/lib/dns"
    fi
fi

# Discover name servers and domain name from resolv.conf
resconf=/etc/resolv.conf
d "Reading domain and nameservers from $resconf."
integer servercount
while read cmd value rest; do
    case $cmd in
	(domain|search): :
		domain=$value	# Compatible with resolver, last one counts.
		;;
	(nameserver): :
		nameservers="${nameservers}${value}; "
		(( servercount+=1 ))
		;;
    esac
done < $resconf

# If servercount is less than three could query server for others, i.e.
# dig ns $domain.

# Check domain and nameservers read.
if [[ -z $domain ]]; then
    e "domain not set in $resconf"
    (( fail++ ))
fi
if [[ -z $nameservers ]]; then
    e "no nameservers found in $resconf"
    (( fail++ ))
fi
(( fail > 0 )) && exit $fail

d "REDACT: Using domain name : $domain"
d "REDACT: Using nameservers : $nameservers"

# Create named.conf file
named_conf=${directory:+$directory/}named.conf
print "
acl \"loopback\" { 127.0.0.1/24; };
options {
	${directory:+directory \"${directory}\";} // working directory
	pid-file \"named.pid\";                   // pid file in working dir.
	forward only;
	forwarders { $nameservers };
	check-names master ignore;
//	allow-query { \"loopback\" };
};

logging {
	channel \"an_example_channel\" {
		file \"example.log\" versions 3 size 20m;
		print-time yes;
		print-category yes;
	};

	category \"default\" { \"an_example_channel\"; \"default_debug\"; };
};



// Be authoritative for example.com
zone \"example.com\" {
	type master;
	file \"example.com.zone\";
};

// All servers should master loopback zones
zone \"0.0.127.in-addr.arpa\" in {
	type master;
	file \"localhost.zone\";
};

" > ${named_conf}

server=$(uname -n).${domain}.
email='root'.${server}
# While todays date is the norm.  serial=$(date +'%Y%m%d00')
# Let's keep it simple.
serial=20
# Create localhost zone.
print "
\$TTL 2D
0.0.127.IN-ADDR.ARPA.   IN      SOA     ${server} ${email} (
                                                ${serial} ; Serial
                                                3600       ; Refresh
                                                300        ; Retry
                                                3600000    ; Expire
                                                14400 )    ; Negative TTL
                        IN      NS      localhost.
1                       IN      PTR     localhost.
" > ${directory:+$directory/}localhost.zone
# Create example.com zone
print "
\$TTL 2D
example.com. IN    SOA     ${server} ${email}  (
                                ${serial}      ; Serial
                                3600            ; Refresh
                                300             ; Retry
                                3600000         ; Expire
                                5m )            ; Negative TTL

                        IN      NS      ${server}

xxx			IN      A       192.168.0.1
			IN      TXT     \"text for xxx.example.com\"

ipv4			IN	A	192.168.4.1
ipv6			IN	AAAA	fd10:45df:879f:661d:0::1
ipboth			IN	TXT	\"Both IP address types\"
ipboth			IN	A	192.168.4.10
ipboth			IN	AAAA	fd10:45df:879f:661d:0::10

manny.sub.example.com.	IN      A       192.168.7.11
			IN	TXT	\"Manny has alias of jack.\"
jack.sub.example.com.	IN      CNAME   manny.sub.example.com.
mo.bar.example.com.	IN      A       192.168.5.17
dname.example.com.		IN      DNAME   sub.example.com.

" > ${directory:+$directory/}example.com.zone

d "Verifying initial named.conf file."
run ${SBIN}/named-checkconf -z ${named_conf} || ret=$?
if [[ $ret -ne 0 ]]; then
    e "Error: named-checkconf returned with non-zero exit code: $ret"
    exit $ret
fi

# Add key and control information to named.conf
#
# Originally ran rndc-confgen to generate a unique config and massaged
# it into named.conf.  But it is just as wise to write direct.
rndc_conf=${directory:+$directory/}rndc.conf
key_value='LydFuYW4OBuN26vWfyMnhQ=='
key_name='rndc-key'
print "
key \"${key_name}\" {
      algorithm hmac-md5;
      secret \"${key_value}\";
};

controls {
      inet 127.0.0.1 port ${rndc_port}
              allow { 127.0.0.1; } keys { \"${key_name}\"; };
};
" >> ${named_conf}
# Write rndc.conf file with key and options.
print "
key \"${key_name}\" {
        algorithm hmac-md5;
        secret \"${key_value}\";
};

options {
        default-key \"${key_name}\";
        default-server 127.0.0.1;
        default-port ${rndc_port};
};
" > ${rndc_conf}

d "Verifying configuration after key and controls added."
run ${SBIN}/named-checkconf -z ${named_conf}

d "starting DNS server"
run ${SBIN}/named -c ${named_conf} -p ${bind_port}

d "checking for pid file"
for (( i=0; i<5; i++ )); do
    if [[ -f $directory/named.pid ]]; then
	pid=$(<$directory/named.pid)
	d "read named.pid"
	break
    else
	sleep 1
    fi
done
if [[ -z $pid ]]; then
    e 'failed to read named.pid'
    # carry on regardless
fi

d "Turning on tracing"
run ${SBIN}/rndc -c ${rndc_conf} trace 3

d "Look-up IPv4 (A) record"
run ${BIN}/dig @0 -p ${bind_port} -t A ipboth.example.com.

d "Look-up IPv6 (AAAA) record"
run ${BIN}/dig @0 -p ${bind_port} -t AAAA ipboth.example.com.

d "Look-up known (ANY) records"
run ${BIN}/dig @0 -p ${bind_port} -t ANY ipboth.example.com.

d "Request zone transfer (axfr)"
run ${BIN}/dig @0 -p ${bind_port} -t axfr example.com.

d "looking up host known to have DNAME"
run ${BIN}/dig @0 -p ${bind_port} -t a jack.dname.example.com.

d "Requesting status"
run ${SBIN}/rndc -c ${rndc_conf} status > $directory/rndc_status

d "Requesting dump of server's caches and zones"
run ${SBIN}/rndc -c ${rndc_conf} dumpdb -all

d "Requesting BIND to stop"
run ${SBIN}/rndc -c ${rndc_conf} stop

# Wait for upto five seconds for server to shutdown.
if [[ -n $pid && -f $directory/named.pid ]]; then
    for (( t=0; t<5; t++ )); do
	if [[ -f $directory/named.pid ]]; then
	    sleep 1 # Give it a second to shutdown...
	else
	    break
	fi
    done
fi

d "REDACT: $directory/named.pid counter $t"

d "Requesting status - should fail as server has stopped."
run -e 1 ${SBIN}/rndc -c ${rndc_conf} status

# Make sure named has exited.
if [[ -n $pid && -f $directory/named.pid ]]; then
    sleep 1 # Give it a second to die...
    if [[ -f $directory/named.pid ]]; then
	e "Warning: named still running, sending SIGTERM to $pid"
	ps -lp $pid | grep named && kill $pid
    fi
fi

exit $ret
