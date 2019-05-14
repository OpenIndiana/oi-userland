#!/usr/bin/ksh93
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
# Copyright (c) 2008, 2010, Oracle and/or its affiliates. All rights reserved.
#
# Description: Check the mounted removable media
#              on the system. For example, cd/dvd,
#              usb disk etc.
#              So far, only probe_s() function is being
#              used.
#              probe() and mount()/umount() function are
#              for furture use.

builtin chmod
builtin cp
builtin mkdir
builtin mv
builtin rm
builtin rmdir
builtin cat

#
# Set trap
#
trap 'clean_up;exit 10' KILL INT
trap 'clean_up' EXIT

PATH=/usr/bin:/usr/sbin:$PATH; export PATH
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/ddu/lib; export LD_LIBRARY_PATH
typeset -r base_dir=$(dirname $0)
typeset -r platform=$(uname -p)
typeset -r bin_dir=$(echo $base_dir | sed 's/scripts$/bin\//')${platform}
typeset    err_log=/tmp/ddu_err.log

function clean_up
{
    {
        rm -f  $rf_file
    }>/dev/null 2>&1
}

#
# Probe for mounted removable media and output the info with the format:
# device path:device name:mount status:mount path
#
function probe_s
{
    rf_file=/tmp/find.media.$$
    typeset dev_path name mp dev_name
    #
    #Ouput cd devices
    #

    #
    # Set carriage return to IFS
    #
    IFS='
'
    for i in $(/usr/bin/pfexec ${bin_dir}/cd_detect -l | \
        awk -F'|' '{print $1,"|",$2}' 2>>$err_log); do

        dev_path=$(echo $i | cut -d'|' -f1 | sed 's/rdsk/dsk/' | tr -d " ")
        name=$(echo $i | cut -d'|' -f2 | tr -d " ")
        /usr/sbin/mount | grep $dev_path >/dev/null 2>&1
        if [ $? -eq 0 ]; then
            mp=$(/usr/sbin/mount | grep $dev_path 2>/dev/null \
                | nawk  -F" on " '{print $1}')
            print -u1 "${dev_path}|${name}|Mounted|$mp"
        fi
    done

    #
    #Output Usb Disk
    #
    pfexec ${bin_dir}/hd_detect -r >$rf_file 2>>$err_log
    
    for i in \
        $(pfexec /usr/sbin/format -e 2>/dev/null </dev/null \
        | sed -n '/^    /p' | grep "^ *[0-9]" \
        | sed 's/^ *//g' | awk '{print $2}'); do

        #
        # Validate the output format
        #
        echo $i | grep '^[a-z][0-9]' >/dev/null 2>&1
        if [ $? != 0 ]; then
            print "$i is not a valid storage device name." >>$err_log
            continue
        fi

        cat $rf_file | grep $i >/dev/null 2>&1
        #
        # Use mount command to check mount point
        #
        if [ $? -eq 0 ]; then
            dev_path="/dev/dsk/${i}"
            dev_name=$(cat $rf_file | grep $i | cut -d: -f1)
            /usr/sbin/mount | grep $dev_path >/dev/null 2>&1
            if [ $? -eq 0 ]; then
                for i in $(/usr/sbin/mount | grep $dev_path 2>/dev/null); do
                    dev_path_1=$(echo $i | nawk -F" on " '{print $2}' \
                        | awk '{print $1}')
                    mp=$(echo $i | nawk -F" on " '{print $1}')
                    print -u1 "${dev_path_1}|${dev_name}|Mounted|$mp"
                done
            fi
        fi
    done        
    rm -f  $rf_file >/dev/null 2>&1
    
}

#Main()

case  $# in
1) if [ $1 != "probe_s" ]; then
       exit 1
   fi
   $1
;;
*) exit 1
;;
esac
