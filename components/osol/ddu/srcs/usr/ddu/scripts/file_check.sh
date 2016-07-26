#!/bin/ksh93
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
# Description: Calling load_driver.sh or 3rd_drv_ins.sh to install the driver
#              package based on the package type, file name and file path.
#
#              Usage:
#              file_check.sh pkg_type file_name file_path Root_path
#              $1 is package type (IPS, SVR4, DU, UNK and P5I)
#              $2 is file name
#              (it can be *, ne file name, multi file names seperated by comma.) 
#              $3 is file path(it can be the local dir, http/ftp url)
#              $4 is root path for the package. it's optional.

builtin chmod
builtin cp
builtin mkdir
builtin mv
builtin rm
builtin cat

PATH=/usr/bin:/usr/sbin:$PATH; export PATH
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/ddu/lib; export LD_LIBRARY_PATH

typeset -r base_dir=$(dirname $0)
typeset    file_path
typeset -i num

#
# Confirm the correct number of commnad line argument
#
if (( $# < 3 )) || (( $# > 4 )); then
    print -u2 "\n$0: Wrong number of arguments provided..."
    exit 1
fi

#
# Validate the arguments
#

case $1 in
IPS | DU | SVR4 | P5I | UNK);;
*) print -u2 "\n... $0: $1 is not valid."; exit 1;;
esac

if [ ! -z $4 ]; then
    if [ ! -d $4 ]; then
        print -u2 "\n... $0: $4 specified is not a valid path."
        exit 1
    fi
fi



#
#file_path can't be null
#
if [ -z "$3" ]; then
    print -u2 "$0: File path can't be null!"
    exit 1
fi

if [[ ! -x ${base_dir}/load_driver.sh ]]; then
    print -u2 "${base_dir}/load_driver.sh not found."
    exit 1
fi

#
#IPS
#
if [ "$1" == "IPS" ]; then
    ${base_dir}/load_driver.sh "$1" "$2" "$3" "$4"
    if [ $? -ne 0 ]; then
        #
        # Install Failed!
        #
        print -u2 "Error executing: " \
            "${base_dir}/load_driver.sh $1 $2 $3 $4"
        exit 1
    else
        #
        # Install Successful!
        #
        exit 0
    fi
fi

#
#URL
#
#
#Check URL format
#
echo "$3" | egrep -e \
    "((https?|ftp|gopher|telnet|file|notes|ms-help):((//)|(\\\\))[\w\d:#%/;$()~_?\\-=\\\.&]*)" \
    >/dev/null 2>&1
if [ $? -eq 0 ]; then
    if [[ ! -x ${base_dir}/3rd_drv_ins.sh ]]; then
        print -u2 "${base_dir}/3rd_drv_ins.sh not found."
        exit 1
    fi
    ${base_dir}/3rd_drv_ins.sh "$1" "$3/$2" "$4"
    if [ $? -ne 0 ]; then
        #
        # Install Failed!
        #
        print -u2 "Error executing: " \
            "${base_dir}/3rd_drv_ins.sh $1 $3/$2 $4"
        exit 1
    else
        #
        # Install Successful!
        #
        exit 0
    fi
fi

#
#Local dir
#
cd "$3"
file_path="$3"
if [ "$2" == "*" ]; then
    num=1
    #
    # Set carriage return to IFS
    #
    IFS='
'
    for i in $(ls -d -1 * 2>/dev/null); do
        file_name[$num]=$i
        num=$(($num + 1))
    done
elif [ ! -z $(echo $2 | grep ',') ]; then
    num=1
    while :; do
        file_name[$num]=$(echo $2 | cut -d, -f$num | awk '{print $1}')
        if [ -z ${file_name[$num]} ]; then
            break
        fi 
        num=$(($num + 1))
    done
else
    num=1
    file_name[$num]="$2"
fi

err_flag=0

num=1
if [ -z "${file_name[$num]}" ]; then
    ${base_dir}/load_driver.sh "$1" "${file_path}/${file_name[$num]}" "$4"
    if [ $? -ne 0 ]; then
        #
        # Load driver failed
        #
        err_flag=1
    fi
fi
while [ ! -z ${file_name[$num]} ]; do
    ${base_dir}/load_driver.sh "$1" "${file_path}/${file_name[$num]}" "$4"
    if [ $? -ne 0 ]; then
        #
        # Load driver failed
        #
        err_flag=1
    fi
    num=$(($num + 1))
done
if [ $err_flag -ne 0 ]; then
    #
    # Install Failed!
    #
    print -u2 "Error executing: " \
        "${base_dir}/load_driver.sh $1 $2 $3 $4"
    exit 1
else
    #
    # Install Successful!
    #
    exit 0
fi
