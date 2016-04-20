#!/usr/sbin/sh
#
# Copyright (c) 2001, 2016, Oracle and/or its affiliates. All rights reserved.
#

. /lib/svc/share/smf_include.sh

SSHDIR=/etc/ssh
KEYGEN="/usr/bin/ssh-keygen -q"
PIDFILE=$SMF_SYSVOL_FS/sshd.pid

# Checks to see if RSA, and DSA host keys are available
# if any of these keys are not present, the respective keys are created.
create_key()
{
	keypath=$1
	keytype=$2

	if [ ! -f $keypath ]; then
		# 
		# HostKey keywords in sshd_config may be preceded or
		# followed by a mix of any number of space or tabs,
		# and optionally have an = between keyword and
		# argument.  We use two grep invocations such that we
		# can match HostKey case insensitively but still have
		# the case of the path name be significant, keeping
		# the pattern somewhat more readable.
		#
		# The character classes below contain one literal
		# space and one literal tab.
		#
		grep -i "^[ 	]*HostKey[ 	]*=\{0,1\}[ 	]*$keypath" \
		    $SSHDIR/sshd_config | grep "$keypath" > /dev/null 2>&1

		if [ $? -eq 0 ]; then
			echo Creating new $keytype public/private host key pair
			$KEYGEN -f $keypath -t $keytype -N ''
			if [ $? -ne 0 ]; then
				echo "Could not create $keytype key: $keypath"
				exit $SMF_EXIT_ERR_CONFIG
			fi
		fi
	fi
}

remove_key()
{
        keypath=$1
        if [ -f $keypath ]; then
                grep -i "^[     ]*HostKey[      ]*=\{0,1\}[     ]*$keypath" \
                    $SSHDIR/sshd_config | grep "$keypath" > /dev/null 2>&1
                if [ $? -eq 0 ]; then
                        rm -f ${keypath} ${keypath}.pub
                fi
        fi
}

#
# Makes sure, that /etc/ssh/sshd_config does not contain single line
# 'ListenAddress ::'. 
#
# This used to be part of default SunSSH sshd_config and instructed SunSSH
# to listen on all interfaces. For OpenSSH, the same line means listen on all
# IPv6 interfaces.
#
fix_listenaddress()
{
	fbackup="$SSHDIR/sshd_config.pre_listenaddress_fix"
	reason4change="#\n\
# Historically default sshd_config was shipped with 'ListenAddress ::',\n\
# which means 'listen on all interfaces' in SunSSH.\n\
# In OpenSSH this setting means 'listen on all IPv6 interfaces'.\n\
# To avoid loss of service after transitioning to OpenSSH, the following\n\
# line was commented out by the network/ssh service method script on\n\
#     $(date).\n\
# Original file was backed up to $fbackup\n\
#\n\
# "
	expl4log="Historically default sshd_config was shipped with \
'ListenAddress ::', which means 'listen on all interfaces' in SunSSH. \
In OpenSSH this setting means 'listen on all IPv6 interfaces'. \
For both SunSSH and OpenSSH the default behavior when no ListenAddress \
is specified is to listen on all interfaces (both IPv4 and IPv6)."
	msg_not_removed="Custom ListenAddress setting detected in \
$SSHDIR/sshd_config, the file will not be modified. Please, check your \
ListenAddress settings. $expl4log"
	msg_removed="Removing 'ListenAddress ::'. $expl4log Original file has \
been backed up to $fbackup"
	
	# only modify sshd_config, if ssh implementation is OpenSSH
	if [[ "$(ssh -V 2>&1)" == Sun_SSH_* ]]; then
		return 0;
	fi

	# comment '# IPv4 & IPv6' indicates an old default sshd_config
	grep -q '^# IPv4 & IPv6$' $SSHDIR/sshd_config || return 0;

	# backup
	cp $SSHDIR/sshd_config $fbackup

	# if 'ListenAddress ::' is the only ListenAddress line, comment it out
	listen_address=$(grep -i '^[ \t]*ListenAddress' $SSHDIR/sshd_config)
	if [[ "$listen_address" == 'ListenAddress ::' ]]; then
		echo $msg_removed
		awk_prog="/^ListenAddress ::$/ {printf(\"$reason4change\")}\
			  !/^# IPv4 & IPv6$/   {print}"
	elif [[ -z "$listen_address" ]]; then
		# no ListenAddress setting => OK, silently remove comment
		awk_prog="!/^# IPv4 & IPv6$/   {print}"
	else
		# send warning message both to log and console
		echo $msg_not_removed | smf_console
		awk_prog="!/^# IPv4 & IPv6$/   {print}"
	fi;

	sshd_config=$(nawk "$awk_prog" $SSHDIR/sshd_config)
	if [[ $? -ne 0 ]]; then
		echo "Update error! Check your ListenAddress settings."
		return 1;
	else
		# write the fixed content to the file
		echo "$sshd_config" > $SSHDIR/sshd_config
		return 0;
	fi

}

# This script is being used for two purposes: as part of an SMF
# start/stop/refresh method, and as a sysidconfig(1M)/sys-unconfig(1M)
# application.
#
# Both, the SMF methods and sysidconfig/sys-unconfig use different
# arguments..

case $1 in 
	# sysidconfig/sys-unconfig arguments (-c and -u)
'-c')
	create_key $SSHDIR/ssh_host_rsa_key rsa
	create_key $SSHDIR/ssh_host_ed25519_key ed25519
	;;

'-u')
	# sysconfig unconfigure to remove the sshd host keys
	remove_key $SSHDIR/ssh_host_rsa_key
	remove_key $SSHDIR/ssh_host_ed25519_key
	;;

	# SMF arguments (start and restart [really "refresh"])

'start')
	#
	# If host keys don't exist when the service is started, create
	# them; sysidconfig is not run in every situation (such as on
	# the install media).
	# 
	create_key $SSHDIR/ssh_host_rsa_key rsa
	create_key $SSHDIR/ssh_host_ed25519_key ed25519

	#
	# Make sure, that /etc/ssh/sshd_config does not contain single line
	# 'ListenAddress ::'.
	#
	fix_listenaddress

	/usr/lib/ssh/sshd
	;;

'restart')
	if [ -f "$PIDFILE" ]; then
		/usr/bin/kill -HUP `/usr/bin/cat $PIDFILE`
	fi
	;;

*)
	echo "Usage: $0 { start | restart }"
	exit 1
	;;
esac	

exit $?
