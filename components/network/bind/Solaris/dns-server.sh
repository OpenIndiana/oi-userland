#!/sbin/sh

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
# Copyright (c) 2007, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright 2016 Hans Rosenfeld <rosenfeld@grumpf.hope-2000.org>
#
# smf_method(5) start/stop script required for server DNS

. /lib/svc/share/smf_include.sh

mount_chroot ()
{
    c=$1
    shift
    for f in $*; do
        if [ -z "${f}" -o ! -f "${f}" -o \
             -z "${c}" -o ! -d "${c}" ]; then
             exit ${SMF_EXIT_ERR_CONFIG}
        fi

        umount ${c}/${f} >/dev/null 2>&1
        mkdir -p `dirname ${c}/${f}`
        touch ${c}/${f}
        mount -Flofs ${f} ${c}/${f}
    done
}

umount_chroot ()
{
    c=$1
    shift
    for f in $*; do
        umount ${c}/${f} >/dev/null 2>&1
    done
}

get_config ()
{
    configuration_file=/etc/named.conf
    rndc_config_file=/etc/rndc.conf
    rndc_key_file=/etc/rndc.key
    rndc_cmd_opts="-a"
    libraries="/lib/openssl/engines/libpk11.so /usr/lib/security/pkcs11_kernel.so.1"
    cmdopts=""
    checkopts=""
    properties="debug_level ip_interfaces listen_on_port
	threads chroot_dir configuration_file server user"

    for prop in $properties
    do
	value=`/usr/bin/svcprop -p options/${prop} ${SMF_FMRI}`
	if [ -z "${value}" -o "${value}" = '""' ]; then
	    continue;
	fi

	case $prop in
	'debug_level')
	    if [ ${value} -gt 0 ]; then
		cmdopts="${cmdopts} -d ${value}"
	    fi
	    ;;
	'ip_interfaces')
	    case ${value} in
		'IPv4')
		    cmdopts="${cmdopts} -4";;
		'IPv6')
		    cmdopts="${cmdopts} -6";;
		'all')
		    :	# Default is all, therefore ignore.
		    ;;
		*)
		    echo "$I: Unrecognised value in service instance property" >&2
		    echo "$I: options/${prop} : ${value}" >&2
		    ;;
	    esac
	    ;;
	'listen_on_port')
	    if [ ${value} -gt 0 ]; then
		cmdopts="${cmdopts} -p ${value}"
	    fi
	    ;;
	'threads')
	    if [ ${value} -gt 0 ]; then
		cmdopts="${cmdopts} -n ${value}"
	    fi
	    ;;
	'chroot_dir')
	    cmdopts="${cmdopts} -t ${value}"
	    checkopts="${checkopts} -t ${value}"
	    chroot_dir=${value};
	    ;;
	'configuration_file')
	    cmdopts="${cmdopts} -c ${value}"
	    checkopts="${checkopts} ${value}"
	    configuration_file=${value};
	    ;;
	'server')
	    set -- `echo ${value} | /usr/bin/sed -e  's/\\\\//g'`
	    server=$@
	    ;;
	'user')
	    cmdopts="${cmdopts} -u ${value}"
	    cmduser=${value};
	    ;;
	esac
    done

    configuration_dir=$(sed -n -e 's,^[[:space:]]*directory.*"\(.*\)";,\1,p' \
        ${configuration_file})
    [ "${configuration_dir}" == "" ] && configuration_dir=/etc/namedb

    configuration_files=$(sed -n -e \
        "s,^[[:space:]]*file.*\"\(.*\)\";,${configuration_dir}/\1,p" \
        ${configuration_file} | sort -u)
    configuration_files="${configuration_files} ${configuration_file}"    
}

result=${SMF_EXIT_OK}

# Read command line arguments
method="$1"		# %m
instance="$2" 		# %i
contract="$3"		# %{restarter/contract}

# Set defaults; SMF_FMRI should have been set, but just in case.
if [ -z "$SMF_FMRI" ]; then
    SMF_FMRI="svc:/network/dns/server:${instance}"
fi
server="/usr/sbin/named"
checkconf="/usr/sbin/named-checkconf"
I=`/usr/bin/basename $0`

case "$method" in
'start')
    get_config

    # Check configuration file exists.
    if [ ! -f ${configuration_file} ]; then
        msg="$I: Configuration file ${configuration_file} does not exist!"
        echo ${msg} >&2
        /usr/bin/logger -p daemon.error ${msg}
        # dns-server should be placed in maintenance state.
        result=${SMF_EXIT_ERR_CONFIG}
    fi

    # If chroot option is set, note zones(5) are preferred, then
    # configuration file lives under chroot directory.
    if [ "${chroot_dir}" != "" ]; then
        if [ "${chroot_dir}" = "/" ]; then
            msg="$I: chroot_dir must not be /"
            echo ${msg} >&2
            /usr/bin/logger -p daemon.error ${msg}
            # dns-server should be placed in maintenance state.
            exit ${SMF_EXIT_ERR_CONFIG}
        fi

        server="env LD_NOLAZYLOAD=1 ${server}"
	checkconf="env LD_NOLAZYLOAD=1 ${checkconf}"

        mkdir -p ${chroot_dir}

        if [ "${SMF_ZONENAME}" = "global" ]; then
            for dev in crypto log null poll random urandom; do
                rm -f ${chroot_dir}/dev/${dev}
                pax -rw -H -pe /dev/${dev} ${chroot_dir}
            done
        fi

        missing=""
        for dev in crypto null poll random urandom; do
            if [ ! -c ${chroot_dir}/dev/${dev} ]; then
                missing="${missing} ${dev}"
            fi
        done

        if [ ! -z "${missing}" ]; then
            msg="$I: missing device nodes in ${chroot_dir}: ${missing}"
            echo ${msg} >&2
            /usr/bin/logger -p daemon.error ${msg}
            # dns-server should be placed in maintenance state.
            exit ${SMF_EXIT_ERR_CONFIG}
        fi

        mkdir -p ${chroot_dir}/etc/crypto
        echo "/usr/lib/security/pkcs11_kernel.so.1" > ${chroot_dir}/etc/crypto/pkcs11.conf

        mount_chroot ${chroot_dir} ${configuration_files} ${libraries}

        mkdir -p ${chroot_dir}/var/run/named
        chown ${cmduser}:${cmduser} ${chroot_dir}/var/run/named

        configuration_file=${chroot_dir}${configuration_file}
        rndc_config_file=${chroot_dir}${rndc_config_file}
        rndc_key_file=${chroot_dir}${rndc_key_file}
        rndc_cmd_opts="${rndc_cmd_opts} -t ${chroot_dir}"
    fi

    # Check if the rndc config file exists.
    if [ ! -f ${rndc_config_file} ]; then
        # If not, check if the default rndc key file exists.
        if [ ! -f ${rndc_key_file} ]; then
            echo "$I: Creating default rndc key file: ${rndc_key_file}." >&2
            /usr/sbin/rndc-confgen ${rndc_cmd_opts}
            if [ $? -ne 0 ]; then
                echo "$I : Warning: rndc configuration failed! Use of 'rndc' to" \
		    "control 'named' may fail and 'named' may report further error" \
		    "messages to the system log. This is not fatal. For more" \
		    "information see rndc(1M) and rndc-confgen(1M)." >&2
            fi
        fi
    fi

    if [ ${result} = ${SMF_EXIT_OK} ]; then
	${checkconf} -z ${checkopts}
	result=$?
	if [ $result -ne 0 ]; then
            msg="$I: named-checkconf failed to verify configuration"
            echo ${msg} >&2
            /usr/bin/logger -p daemon.error ${msg}
            if [ "${chroot_dir}" != "" -a "${chroot_dir}" != "/" ]; then
                umount_chroot ${chroot_dir} ${configuration_files} ${libraries}
            fi
            # dns-server should be placed in maintenance state.
            exit ${SMF_EXIT_ERR_CONFIG}
	fi
    fi

    if [ ${result} = ${SMF_EXIT_OK} ]; then
	echo "$I: Executing: ${server} ${cmdopts}"
	# Execute named(1M) with relevant command line options.  Note
	# the server forks before reading named.conf(4) and so a
	# good exit code here does not mean the service is ready.
	${server} ${cmdopts}
	result=$?
	if [ $result -ne 0 ]; then
	    echo "$I : start failed! Check syslog for further information." >&2
        fi
    fi
    ;;
'stop')
    get_config

    smf_kill_contract ${contract} TERM 1
    [ $? -ne 0 ] && exit 1

    if [ "${chroot_dir}" != "" -a "${chroot_dir}" != "/" ]; then
        umount_chroot ${chroot_dir} ${configuration_files} ${libraries}
    fi

    ;;
*)
    echo "Usage: $I [stop|start] <instance>" >&2
    exit 1
    ;;
esac
exit ${result}
