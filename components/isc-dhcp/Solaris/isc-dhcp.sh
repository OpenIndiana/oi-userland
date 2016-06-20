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

#
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#

. /lib/svc/share/smf_include.sh
. /lib/svc/share/net_include.sh

SVCPROP=/usr/bin/svcprop
CHMOD=/usr/bin/chmod
CHOWN=/usr/bin/chown
TOUCH=/usr/bin/touch
ID=/usr/bin/id

DHCPD_IPV4="svc:/network/dhcp/server:ipv4"
DHCPD_IPV6="svc:/network/dhcp/server:ipv6"
DHCPRELAY_IPV4="svc:/network/dhcp/relay:ipv4"
DHCPRELAY_IPV6="svc:/network/dhcp/relay:ipv6"

DHCPD_BIN="/usr/lib/inet/dhcpd"
DHCPRELAY_BIN="/usr/lib/inet/dhcrelay"

#
# dhcpd/dhcprelay can run in a global or exclusive-stack zone only
#
smf_configure_ip || exit $SMF_EXIT_OK

if [ -z $SMF_FMRI ]; then
	echo "SMF framework variables are not initialized."
	exit $SMF_EXIT_ERR
fi

#
# get_prop fmri propname
#
get_prop () {
	VALUE="`$SVCPROP -cp config/$1 $SMF_FMRI 2>/dev/null`"
	# Empty astring_list values show up as "" - do not return this.
	if [ "$VALUE" != "\"\"" ]; then
		echo $VALUE
	fi
}

errlog () {
	echo $1 >&2
}

get_common_options() {
	#
	# get debug property value 
	#
	if [ "`get_prop debug`" = "true" ]; then
		DEBUG="-d"
	else
		DEBUG="-q"
	fi

	export OPTIONS="$OPTIONS $DEBUG"
	return 0
}

#
# expand_prop "prop_name" "var_name" [ argflag ]
#
#     prop_name		FMRI property name
#     var_name		variable where result is stored; initialized
#			to ""
#     argflag		The flag to be prepended to each property
#			value; optional argument
#
# This function will retrieve the properties for "prop_name" via a call
# to get_prop(). It will split-up the property values; it assumes that
# the delimiter is whitespace. It will then prepend "argflag" to each
# property value. The results will be stored in "var_name" which is
# passed by reference.
#
# Return values:
#
#     0			Success
#     1			Failure
#
expand_prop() {
	if [ $# -lt 2 ] || [ -z $2 ]; then
		errlog "Internal error - expand_prop() has incorrect arguments"
		return 1
	fi

	prop_name=$1
	typeset -n var_name=$2
	argflag="$3"

	prop_values="`get_prop $prop_name`"
	if [  -z "$prop_values" ]; then
		errlog "The property, \"${prop_name}\", is empty"
		return 1
	fi

	var_name=""
	for item in `IFS= ; set -- $prop_values; echo $@`; do
		var_name="$var_name $argflag $item"
	done

	return 0
}


get_dhcpd_options() {
	# get listen_ifname property value.
	LISTENIFNAMES="`get_prop listen_ifnames`"

	#
	# get common config file properties
	#
	CONFIGFILE=`get_prop config_file`
	if [ -z "$CONFIGFILE" ]; then
		errlog "No config_file specified, exiting"
		return 1
	fi
	if [ ! -f "$CONFIGFILE" ]; then
		errlog "Required config_file $CONFIGFILE not found, exiting"
		return 1
	fi

	#
	# If a leasefile does not exist, create an empty file.
	#
	LEASEFILE=`get_prop lease_file`
	if [ -z "$LEASEFILE" ]; then
		errlog "No lease_file specified, exiting"
		return 1
	fi

	LEASEFILE_PERMS="u=rw,go=r"
	if [ ! -f "$LEASEFILE" ]; then
		$TOUCH $LEASEFILE
		$CHMOD $LEASEFILE_PERMS $LEASEFILE
	fi
	if [ ! -w "$LEASEFILE" ]; then
		errlog "Lease file '$LEASEFILE' is not writable. You should:"
		errlog "$CHOWN $($ID -u -n) '$LEASEFILE'"
		errlog "$CHMOD $LEASEFILE_PERMS '$LEASEFILE'"
		return 1
	fi

	export OPTIONS="$OPTIONS -cf $CONFIGFILE -lf $LEASEFILE $LISTENIFNAMES"
	return 0
}

get_dhcprelay_options_v4() {
	#
	# Get append_agent_option V4 property value 
	#
	if [ "`get_prop append_agent_option`" = "true" ]; then
		APPEND="-a -m append"
	else
		APPEND=""
	fi

	#
	# get listen_ifname property value and modify it.  
	# If listen_ifnames property value is "e1000g01 iprb0" then the
	# command line option will look like  "-i e1000g0 -i iprb0"
	#
	IIFLIST=
	expand_prop listen_ifnames IIFLIST -i || return $?

	#
	# Get servers  V4 property value - command line option will look
	# like  "1.2.3.5" "4.5.6.7".
	#
	# NOTE: By default server property value is empty. User must
	# first specify a server using svccfg/setprop command
	# before enabling service.
	#
	DHCPSERVERS=`get_prop servers`
	if [  -z "$DHCPSERVERS" ]; then
		errlog 'Must specify at least one "servers" property value, exiting'
		return 1
	fi

	export OPTIONS="$OPTIONS -4 $APPEND $IIFLIST $DHCPSERVERS"
	return 0
}

get_dhcprelay_options_v6() {
	#
	# Get receivelinks  V6 property value and modify it:
	# Given property values of "1.2.3.4%bge0#1 bge2,1.2.3.4%iprb",
	# the command line option will look like  "-l 1.2.3.4%bge0#1 -l
	# bge2 -l 1.2.3.4%iprb".
	#
	# NOTE: By default receivelinks value is empty. User must
	# first specify a server using svccfg/setprop command
	# before enabling service.
	#
	IRECVLINKS=
	expand_prop receive_query_links IRECVLINKS -l || return $?
	#
	# Get forwardlinks V6 property value and modify it:
	# Given forward_query_links property value is "1.2.3.4%bge0 bge2,"
	# then the command line option will look like  "-u 1.2.3.4%bge0 -u
	# bge2"
	#
	# NOTE: By default forwardlinks value is empty. User must
	# first specify a server using svccfg/setprop command
	# before enabling service.
	#
	IFWDLINKS=
	expand_prop forward_query_links IFWDLINKS -u || return $?

	export OPTIONS="$OPTIONS -6 $IRECVLINKS $IFWDLINKS"
}

export OPTIONS="--no-pid"

case "$SMF_FMRI" in
"$DHCPD_IPV4"|"$DHCPD_IPV6")
	# get omapi_conn_limit property value.
	export OMAPI_CONN_LIMIT=`get_prop omapi_conn_limit`

	get_common_options
	if [ "$?" != "0" ]; then
		exit $SMF_EXIT_ERR_CONFIG
	fi
	get_dhcpd_options
	if [ "$?" != "0" ]; then
		exit $SMF_EXIT_ERR_CONFIG
	fi
	if [ "$SMF_FMRI" = "$DHCPD_IPV4" ]; then
		OPTIONS="-4 $OPTIONS"
	else
		OPTIONS="-6 $OPTIONS"
	fi
	export EXECFILE=$DHCPD_BIN
	;;

$DHCPRELAY_IPV4)
	get_common_options
	if [ $? != "0" ]; then
		exit $SMF_EXIT_ERR_CONFIG
	fi
	get_dhcprelay_options_v4
	if [ $? != "0" ]; then
		exit $SMF_EXIT_ERR_CONFIG
	fi
	export EXECFILE=$DHCPRELAY_BIN
	;;

$DHCPRELAY_IPV6)
	get_common_options
	if [ $? != "0" ]; then
		exit $SMF_EXIT_ERR_CONFIG
	fi
	get_dhcprelay_options_v6
	if [ $? != "0" ]; then
		exit $SMF_EXIT_ERR_CONFIG
	fi
	export EXECFILE=$DHCPRELAY_BIN
	;;

*)
        echo "isc-dhcp must be invoked from within SMF"
        exit $SMF_EXIT_ERR_FATAL
	;;

esac

# Now start the daemon
if [ "$DEBUG" = "-d" ]; then
	$EXECFILE $OPTIONS &
else
	$EXECFILE $OPTIONS
fi

if [ "$?" != "0" ]; then
	exit $SMF_EXIT_ERR_FATAL
fi

exit $SMF_EXIT_OK
