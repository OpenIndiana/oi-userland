#!/sbin/sh
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
# Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
#ident	"@(#)tor.sh	1.1	09/05/14 SMI"
#

. /lib/svc/share/smf_include.sh

# SMF_FMRI is the name of the target service. This allows multiple instances 
# to use the same script.

if [ -z "$SMF_FMRI" ]; then
	echo "SMF framework variables are not initialized."
	exit $SMF_EXIT_ERR
fi

tor_start() 	{
	# Raise the number of file descriptors
	/usr/bin/ulimit -n 1024 2>&1 > /dev/null
	/usr/bin/tor 2>&1 > /dev/null
}
	
tor_stop()	{
	/usr/bin/pkill -x tor 2>&1 > /dev/null
}

#
# Parse the various "*Port" and "*ListenAddress" parameters
# from the Tor config file (/etc/torrc) and create IPF rules.
#
find_ports()
{
	port=$1
	addr=$2

	# If this is non-zero, it is in use.
	p=`grep "^$port" /etc/torrc 2>/dev/null | \
		awk '{print $2}'`

	if [ ! -z "$p" ]; then
		echo "# Tor $port rules" >> ipf_file
	fi

	for i in $p; do
		generate_rules $FMRI $policy "tcp" "any" $i $ipf_file
	done

	# Alternate *Address parameter may specify another port
	a=`grep "^$addr" /etc/torrc 2>/dev/null | \
		awk '{print $2}'`

	if [ ! -z "$a" ]; then
		echo "# Tor $addr rules" >> $ipf_file
	fi

	for i in $a; do
		p=`echo "$i" | sed -e 's/.*://'`
		ip=`echo "$i" | sed -e 's/:.*//'`
		#
		# We don't need to add 0.0.0.0 IP
		#
		if [ "$ip" = "0.0.0.0" ]; then
			ip=''
		fi
		if [ ! -z "$p" ]; then
			generate_rules $FMRI $policy "tcp" "any" $ip $p $ipf_file
		fi
	done
	return $?
}

create_ipf_rules()
{
	FMRI=$1

	#
	# If Tor is not configured, there are no rules to add
	#
	if [  ! -f /etc/torrc ]; then
		return;
	fi

	ipf_file=`fmri_to_file ${FMRI} $IPF_SUFFIX`
	policy=`get_policy ${FMRI}`

	echo "# $FMRI" >$ipf_file

	#
	# Tor may be configured to listen on a specific Port or
	# it may be configured to a specific interface:port combination
	# so we look for both parameters for the various Tor ports in the
	# config file.
	#
	find_ports SocksPort SocksListenAddress

	find_ports ORPort ORListenAddress

	find_ports DirPort DirListenAddress

	find_ports HiddenServicePort __no_addr_param__

	find_ports ControlPort __no_addr_param__
}

case "$1" in
'start')
	tor_start 
	;;

'stop')
	tor_stop
	;;

'ipfilter')
	create_ipf_rules $2
	;;

*)
	echo "Usage: $0 {start|stop|ipfilter}"
	exit 1
	;;

esac
exit $SMF_EXIT_OK
