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
# Copyright (c) 2008, 2010, Oracle and/or its affiliates. All rights reserved.
#
# Description: Download the driver package from the
#              network, use pkg_check.sh to uncompress
#              the package if the package is compressed,
#              then use load_driver.sh to install the 
#              driver.
#
#              Usage:
#              3rd_drv_int.sh pkg_type download_url root_path
#              $1 is for package type.(IPS, DU, SVR4, P5I, UNK)
#              $2 is the driver download URL 
#              $3 is root path for installation, can be null.
#

builtin chmod
builtin cp
builtin mkdir
builtin mv
builtin rm
builtin cat


function clean_up
{
    {
        if [ -s $f_dir_file ]; then
            for f_dir in $(cat $f_dir_file); do
                rm -f $f_dir
            done
            rm -f $f_dir_file
         fi
         if [ -s $pkg_loc ]; then
             d_name=$(echo $pkg_loc | cut -d'/' -f3)
             cd /tmp; rm -rf $d_name
         fi
    } >/dev/null 2>&1
}


#Main()

trap 'clean_up;exit 10' KILL INT
trap 'clean_up' EXIT

PATH=/usr/bin:/usr/sbin:$PATH; export PATH
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/ddu/lib; export LD_LIBRARY_PATH

#
# Confirm the correct number of commnad line argument
#
if (( $# < 2 )) || (( $# > 3 )); then
    print -u2 "\n $0: Wrong number of arguments provided..."
    exit 1
fi

#
# Validate the arguments
#

case $1 in
IPS | DU | SVR4 | P5I | UNK);;
*) print -u2 "\n... $0: $1 is not valid."; exit 1;;
esac

echo "$2" | egrep -e \
    "((https?|ftp|gopher|telnet|file|notes|ms-help):((//)|(\\\\))[\w\d:#%/;$()~_?\\-=\\\.&]*)" \
    >/dev/null 2>&1

if [ $? -ne 0 ]; then
    print -u2 "\n... $0: $2 is not valid URL."
    exit 1
fi

if [ ! -z $3 ]; then
    if [ ! -d $3 ]; then
        print -u2 "\n... $0: $3 specified is not a valid path."
        exit 1         
    fi
fi

typeset -r base_dir=$(dirname $0)
typeset    pkg_type="$1"
typeset -r root_path="$3"

print -u1 "\nDownloading from URL $2 ..."

if [[ ! -x $base_dir/url_down.py ]]; then
    print -u2 "$base_dir/url_down.py not found."
    exit 1
fi

typeset    pkg_info pkg_type pkg_loc
typeset -r f_dir_file=/tmp/f_dir_file_$$


try_time=0
while [ $try_time -le 5 ]; do
    $base_dir/url_down.py download "$2" > $f_dir_file
    if [ $? -ne 0 ]; then
        sleep 10 &
        idle_time=$!
        while [ -d /proc/${idle_time} ]; do
            :
        done
        try_time=$((try_time + 1))  
    else
        break
    fi
done      


if [ $try_time -le 5 ] && [ -s $f_dir_file ]; then
    for f_dir in $(cat $f_dir_file); do
        7za t "$f_dir" >/dev/null 2>&1
        if [ $? -eq 0 ]; then
        #
        # For compressed data
        #
            if [[ ! -x $base_dir/pkg_check.sh ]]; then
                print -u2 "$base_dir/pkg_check.sh not found."
                exit 1
            fi
    
            if [[ ! -x $base_dir/load_driver.sh ]]; then
                print -u2 "$base_dir/load_driver.sh not found."
                exit 1
            fi
    
            pkg_info=$($base_dir/pkg_check.sh $f_dir)
            if [ $? -eq 0 ] && [ ! -z $pkg_info ]; then
                for i in $pkg_info; do
                    pkg_type=$(echo $i | cut -d'|' -f1)
                    pkg_loc=$(echo $i | cut -d'|' -f2)
                    if [ ! -z $pkg_type ] && [ ! -z $pkg_loc ]; then
                        #
                        # Add quote for $pkg_loc for spaces in the variable
                        #
    
                        $base_dir/load_driver.sh $pkg_type "$pkg_loc" $root_path
                        if [ $? -ne 0 ]; then
                            print -u2 "Error executing: $base_dir/load_driver.sh."
                            exit 1
                        fi
                    else
                        print -u2 "Package type and location can not be null."
                        exit 1
                    fi
                done
            else
                print -u2 "Error executing: $base_dir/pkg_check.sh."
                exit 1
            fi
        else 
            #
            # plain file
            #
            #
            # Add quote for $f_dir for spaces in the variable
            #
            $base_dir/load_driver.sh $pkg_type "$f_dir" $root_path
            if [ $? -ne 0 ]; then
                print -u2 "Error executing: $base_dir/load_driver.sh."
                exit 1
            fi
        fi
    done
else
    print -u2 "\nDownload $2 failed!"
    exit 1
fi
