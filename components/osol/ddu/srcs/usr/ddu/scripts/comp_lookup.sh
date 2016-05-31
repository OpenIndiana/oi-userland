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
#
# Description: Use device compatible name to search for available driver
#              by IPS or local driver db.
#
#              Usage:
#              comp_lookup.sh $1 $2              
#              $1 is for compatible string
#              $2 is IPS publisher name, optional
#

builtin chmod
builtin cp
builtin mkdir
builtin mv
builtin rm
builtin cat


PATH=/usr/bin:/usr/sbin:$PATH; export PATH
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/ddu/lib; export LD_LIBRARY_PATH

#
# Confirm the correct number of commnad line argument
#
if (( $# < 1 )) || (( $# > 2 )); then
    exit 1
fi

#
# Confirm the $1 is not null
#
if [ -z "$1" ]; then
   exit 1
fi

typeset -r base_dir=$(dirname $0)
typeset -r platform=$(uname -p)
typeset -r bin_dir=$(echo $base_dir |sed 's/scripts$/bin\//')"$platform"
typeset matched_drv=
typeset matched_drv_pkg_type=UNK #SVR4,IPS,DU,P5I,UNK
typeset com_name_str=$1
typeset repo_candi=$2
typeset err_log=/tmp/ddu_err.log

#
# Search through IPS for missing device driver by device 
# compatible string.
#
function find_driver
{
    typeset s_result_file=/tmp/s_result.$$
    typeset ret_val s_result def_repo drv_type candi_drv

    if [[ ! -x $base_dir/pkg_relate.sh ]]; then
        echo "Can not find $base_dir/pkg_relate.sh or not executable." \
            >>$err_log
        exit 1
    fi

    #
    # Search for missing driver package via IPS
    #
    if [ ! -z "$repo_candi" ]; then
	ret_val=1
	for repo_index in $repo_candi; do
	    for com_name in $com_name_str; do
        	if [ ! -z "$com_name" ]; then
		    $base_dir/pkg_relate.sh search $com_name $repo_index \
                        > $s_result_file 2>>$err_log
		    if [ $? == 0 ]; then
			ret_val=0
			break
		    fi
		fi
	    done
	    if [ $ret_val -eq 0 ]; then
		s_result=$(cat $s_result_file)
		break
	    fi	
	done
    else
	ret_val=1
	def_repo=$($base_dir/pkg_relate.sh list default \
            2>>$err_log | awk '{print $1}' | uniq)
	for com_name in $com_name_str; do
            if [ ! -z "$com_name" ]; then
		$base_dir/pkg_relate.sh search $com_name $repo_candi \
                    > $s_result_file 2>>$err_log
            fi
            ret_val=$?
            if [ $ret_val -eq 0 ]; then
                cat $s_result_file | grep $def_repo >/dev/null 2>&1
                if [ $? -eq 0 ]; then
                    s_result=$(cat $s_result_file | grep $def_repo | sort \
                        | tail -1)
                else
                    s_result=$(cat $s_result_file | sort | tail -1)
                fi
                break
            fi
	done
    fi
    if [ $ret_val -eq 0 ] && [ ! -z $s_result ]; then
        matched_drv=$com_name
        matched_drv_pkg_type=IPS
        echo $s_result | awk '{print $1}' > /tmp/${matched_drv}_info.tmp    
        echo $s_result | awk '{print $2}' > /tmp/${matched_drv}_dlink.tmp    
    else
        #
        # Search for the missing driver package via local driver db
        #

        if [[ ! -x ${bin_dir}/find_driver ]]; then
            echo "Can not find ${bin_dir}/find_driver or not executable." \
                >>$err_log
            exit 1
        fi
        candi_probe=$(${bin_dir}/find_driver -n "$com_name_str")
        if [ $? -eq 0 ]; then
            candi_drv=$(echo $candi_probe | cut -d'|' -f2)
            if [ ! -z "$candi_drv" ]; then
                def_repo=$($base_dir/pkg_relate.sh list default \
                    2>>$err_log | awk '{print $1}' | uniq)
                $base_dir/pkg_relate.sh search $candi_drv \
                    > $s_result_file 2>>$err_log
                ret_val=$?
                if [ $ret_val -eq 0 ]; then
                    cat $s_result_file | grep $def_repo >/dev/null 2>&1
                    if [ $? -eq 0 ]; then
                        s_result=$(cat $s_result_file | grep $def_repo \
                            | sort | tail -1)
                    else
                        s_result=$(cat $s_result_file | sort | tail -1)
                    fi
                fi

		#
		#drv_type:
		# 1: Solaris Driver
		# 2: Third-Party Driver
		# 3: Opensolaris Driver,
		# 4: No Driver found"
		#
                if [ $ret_val -eq 0 ] && [ ! -z $s_result ]; then
                    matched_drv=$candi_drv
                    matched_drv_pkg_type=IPS
                    echo $s_result | awk '{print $1}' \
                        > /tmp/${matched_drv}_info.tmp    
                    echo $s_result | awk '{print $2}' \
                        > /tmp/${matched_drv}_dlink.tmp    
                else
                    drv_type=$(echo $candi_probe | cut -d'|' -f1)
                    if [ "$drv_type" -eq 2 ] || [ "$drv_type" -eq 3 ]; then
                        matched_drv=$(echo $candi_probe | cut -d'|' -f2)
                        matched_drv_pkg_type=$(echo $candi_probe | cut -d'|' -f5)
                        echo $candi_probe | cut -d'|' -f3 \
                            > /tmp/${matched_drv}_info.tmp
                        echo $candi_probe | cut -d'|' -f6 \
                            > /tmp/${matched_drv}_dlink.tmp
                    fi
                fi
            fi
        fi
    fi
    if [ ! -z ${matched_drv} ]; then
        pfexec chmod 666 /tmp/${matched_drv}_info.tmp \
            /tmp/${matched_drv}_dlink.tmp >/dev/null 2>&1
    fi
}


#main
find_driver 
print -u1 "$matched_drv:$matched_drv_pkg_type"
