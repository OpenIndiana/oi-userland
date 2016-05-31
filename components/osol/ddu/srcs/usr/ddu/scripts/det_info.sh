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
# Description: Output the device detail information to a file 
#              under /tmp
#              $1 is the device path
#              $2 class code, optional

builtin chmod
builtin cp
builtin mkdir
builtin mv
builtin rm
builtin cat

function clean_up
{
    {
         rm -rf $disk_info
    } >/dev/null 2>&1
}


trap 'clean_up;exit 10' KILL INT
trap 'clean_up' EXIT

PATH=/usr/bin:/usr/sbin:$PATH; export PATH
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/ddu/lib; export LD_LIBRARY_PATH

typeset    err_log=/tmp/ddu_err.log

#
# Confirm the correct number of commnad line argument
#
if (( $# < 1 )) || (( $# > 2 )); then
    echo "$0: Invalid argument..." >>$err_log
    exit 1
fi

typeset -r base_dir=$(dirname $0)
typeset -r platform=$(uname -p)
typeset    bin_dir=$(echo $base_dir |sed 's/scripts$/bin\//')"$platform"
#
# Class code, more detail please refer /usr/include/sys/pci.h
#
typeset    c1="CLASS=000100|CLASS=000101|CLASS=000104|CLASS=000105"
typeset    c2="|CLASS=000106|CLASS=000107|CLASS=000180|CLASS=000c04"
typeset    str_class_code="${c1}${c2}"
typeset    class_code o_file d_path hd_info disk_info
typeset    disk_name disk_path disk_driver disk_capacity

if [ -z "$1" ]; then
    echo "$0: Invalid argument..." >>$err_log
    exit 1
else
    dev_path=$1
fi

if [ "$1" == "cpu" ] || [ "$1" == "memory" ]; then
    o_file="$1"_"$$"

    if [[ ! -x ${bin_dir}/dmi_info ]]; then
        echo "$0: ${bin_dir}/dmi_info not found or not executable." \
             >>$err_log 
        exit 1
    fi

    #
    #Output the file name for GUI
    #
    print -u1 "/tmp/$o_file"

    if [ "$1" == "cpu" ]; then
        ${bin_dir}/dmi_info -C >/tmp/$o_file 2>>$err_log
    else
        ${bin_dir}/dmi_info -m >/tmp/$o_file 2>>$err_log
    fi
else
    o_file=$(echo $dev_path | tr -d '/@,')

    if [[ ! -x ${bin_dir}/all_devices ]]; then
        echo "$0: ${bin_dir}/all_devices not found or not executable." \
             >>$err_log 
        exit 1
    fi

    #
    #Output the file name for GUI
    #
    print -u1 "/tmp/$o_file" 

    ${bin_dir}/all_devices -v -d $dev_path >/tmp/$o_file 2>>$err_log
fi

chmod 666 /tmp/"$o_file" 2>/dev/null

if [ "$(wc /tmp/"$o_file" 2>/dev/null | awk '{print $1}')" -le 1 ]; then
    if [[ ! -x ${bin_dir}/bat_detect ]]; then
        echo "$0: ${bin_dir}/bat_detect not found or not executable." \
             >>$err_log 
        exit 1
    fi
    ${bin_dir}/bat_detect -d $dev_path >/tmp/$o_file 2>>$err_log
fi

if [ -z "$2" ]; then
    exit 0
else
    class_code=$2
fi

echo $class_code |  egrep ${str_class_code} >/dev/null 2>&1

if [ $? == 0 ]; then
    #
    # Set carriage return to IFS
    #
    IFS='
'
    d_path=$(echo $1 | cut -d: -f1)
    if [[ ! -x ${bin_dir}/hd_detect ]]; then
        echo "$0: ${bin_dir}/hd_detect not found or not executable." \
             >>$err_log 
        exit 1
    fi
    hd_info=$(pfexec ${bin_dir}/hd_detect -c $d_path | sort | uniq)
    if [ ! -z "$hd_info" ]; then
        disk_info=/tmp/disk_info_tmp
        for i in "$hd_info"; do
            disk_name=$(echo $i | cut -d: -f1)
            disk_path=$(echo $i | cut -d: -f3)
            pfexec ${bin_dir}/hd_detect -m $disk_path > $disk_info
            disk_driver=$(cat  $disk_info | grep driver | awk -F: '{print $2}')
            disk_capacity=$(cat $disk_info | grep Capacity | awk -F: '{print $2}')    
            print -u1 "DISK :    ${disk_name}" >>/tmp/$o_file
            print -u1 "   Capacity :    ${disk_capacity}" >>/tmp/$o_file
            print -u1 "   Driver   :    ${disk_driver}" >>/tmp/$o_file
            print -u1 "   Path     :    ${disk_path}" >>/tmp/$o_file
            print -u1 "    " >>/tmp/$o_file
        done
    fi
fi
