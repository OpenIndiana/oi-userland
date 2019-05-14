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
# Description: Perform pkg related function: 
#              list repo, add repo, search repo and modify
#              repo etc.
#
#              Usage:
#              pkg_relate.sh $1 $2
#              $1 can be "add","list","search" and "modify"
#              $2 is the sub-argument for $1
#              $3 is the sub-argument for $1
#

builtin chmod
builtin cp
builtin mkdir
builtin mv
builtin rm
builtin cat
builtin printf

#
# Get all publishers info on the system
#
function fetch_repo
{
    pfexec pkg publisher -H > /tmp/repo_temp_store 2>>$err_log
    if [ $? -ne 0 ]; then
        print -u2 "$0: Error found when getting repo list"
        exit 1
    fi
    repo_list=$(cat /tmp/repo_temp_store | cut -d " " -f 1 2>/dev/null)
    repo_url=$(cat /tmp/repo_temp_store | nawk -F"http://" '{ print $2 }' \
        2>/dev/null)
    repo_count=$(cat /tmp/repo_temp_store | wc -l 2>/dev/null)
}

#
# Output the publisher info in the following format:
# opensolaris.org http://ipkg.sfbay.sun.com/dev/
#

function print_repo
{
    index=1
    while [ $index -le ${repo_count} ]; do
        repo_listi=$(echo ${repo_list} | nawk '{ print $'${index}' }')
        repo_urli=$(echo ${repo_url} | nawk '{ print $'${index}' }')
        printf "${repo_listi}\thttp://${repo_urli}\n"
        index=$(($index + 1))
    done
}

#
# Output the publisher info with following format based on the input 
# parameter:
# opensolaris.org http://ipkg.sfbay.sun.com/dev/
#
# Input paramenters can be:
# all:            list all the publisher info.
# default:        list preferred publisher info.
# publisher name: list specified pulibsher info.
#

function list
{
    if [ ${min_argu_1} == "all" ]; then #list all repo.
        fetch_repo
        print_repo
    elif [ ${min_argu_1} == "default" ]; then #list default repo
        pfexec pkg publisher -HP > /tmp/repo_default_store 2>>$err_log
        repo_list=$(cat /tmp/repo_default_store | cut -d " " -f 1 2>/dev/null)
        repo_url=$(cat /tmp/repo_default_store | nawk -F"http://" '{ print $2 }' \
            2>/dev/null)
        repo_count=$(cat /tmp/repo_default_store | wc -l 2>/dev/null)
        print_repo
    elif [ ! -z ${min_argu_1} ]; then #list a specific repo
	repo_name=${min_argu_1}
        pfexec pkg publisher ${repo_name} | grep "URI" \
            > /tmp/repo_spe_store 2>>$err_log
        if [  $? != 0 ]; then
            print -u2 "$0: ${repo_name} is not a valid repo name!"
            exit 1
        fi
        repo_url=$(cat /tmp/repo_spe_store | nawk -F"http://" '{ print $2 }' \
            2>/dev/null)
	for repo_urli in ${repo_url}
	do
	    repo_url="http://"${repo_urli}
	    printf "${repo_name}\t${repo_url}\n"
	done
    fi
}

#
# Search for driver package via pulisher based on the device compatible string 
# 
function search
{
    if [ -z ${min_argu_2} ]; then
        pakcage_found=0
        fetch_repo
    
        index=1
        while [ $index -le ${repo_count} ]; do
            repo_listi=$(echo ${repo_list} | nawk '{ print $'${index}' }')
            repo_urli=$(echo ${repo_url} | nawk '{ print $'${index}' }')

            repo_urli="http://"${repo_urli}
    
            pfexec pkg search -p -s "${repo_urli}" "${min_argu_1}" \
               2>>/dev/null | nawk -F"@" '{ print $1 }' | \
               nawk -F"pkg:/" '{ print $2 }' | uniq > /tmp/pkg_candi

            pkgname=$(grep driver /tmp/pkg_candi | tail -1 2>/dev/null)
            if [ -z ${pkgname} ]; then
                pkgname=$(tail -1 /tmp/pkg_candi 2>/dev/null)
            fi

            if [[ $? != 0  ||  -z ${pkgname} ]]; then
                index=$(($index + 1))
                continue
            fi
		
	    depend_str="depend:incorporate:${pkgname}" 
	    pkg_ver=$(pfexec pkg search -l ${depend_str} | tail -1 2>>/dev/null)

	    if [ $? -eq 0 ]; then
                pkgvalue=$(echo ${pkg_ver} | nawk '{ print $3 }')
                if [ -z "`echo ${pkgvalue} | grep "pkg:/"`" ]; then
		    pkgcondidate=${pkgvalue}
                else
                    pkgcondidate=$(echo ${pkgvalue} | nawk -F"pkg:/" '{ print $2 }')
                fi
	    fi

            if [ -z ${pkgcondidate} ]; then
                pkgcondidate=${pkgname}
            fi
            pfexec pkg info -r pkg://${repo_listi}/${pkgcondidate} \
                >/dev/null 2>>$err_log
            if [ $? -eq 0 ]; then
                /usr/bin/printf "${repo_listi}\t${pkgcondidate}\n"
                pakcage_found=1
            fi    
            index=$(($index + 1))
        done
    else
        repo_listi=${min_argu_2}
	pakcage_found=0
        repo_urli=$(pfexec pkg publisher ${repo_listi}  | grep "URI" \
            | nawk -F"http://" '{ print $2 }')

        for repo_urli_i in $repo_urli; do
            repo_urli_i="http://"${repo_urli_i}

            pfexec pkg search -p -s "${repo_urli_i}" "${min_argu_1}" \
              2>>/dev/null | nawk -F"@" '{ print $1 }' | \
              nawk -F"pkg:/" '{ print $2 }' | uniq > /tmp/pkg_candi

            pkgname=$(grep driver /tmp/pkg_candi | tail -1 2>/dev/null)
            if [ -z ${pkgname} ]; then
                pkgname=$(tail -1 /tmp/pkg_candi 2>/dev/null)
            fi
            if [ ! -z ${pkgname} ]; then
                break
            fi
        done
        
        if [[ $? != 0  ||  -z ${pkgname} ]]; then
            exit 1
        fi

        depend_str="depend:incorporate:${pkgname}" 
        pkg_ver=$(pfexec pkg search -l ${depend_str} | tail -1 2>>/dev/null)

        if [ $? -eq 0 ]; then
            pkgvalue=$(echo ${pkg_ver} | nawk '{ print $3 }')
            if [ -z "`echo ${pkgvalue} | grep "pkg:/"`" ]; then
	        pkgcondidate=${pkgvalue}
            else
                pkgcondidate=$(echo ${pkgvalue} | nawk -F"pkg:/" '{ print $2 }')
            fi
	fi

        if [ -z ${pkgcondidate} ]; then
            pkgcondidate=${pkgname}
        fi
        pfexec pkg info -r pkg://${repo_listi}/${pkgcondidate} \
            >/dev/null 2>>$err_log
        if [ $? -eq 0 ]; then
            printf "${repo_listi}\t${pkgcondidate}\n"
            pakcage_found=1
        fi    
    fi
    if [ ${pakcage_found} -eq 0 ]; then
        exit 1
    fi
}

#
# Add publisher on the system
#

function add
{
    #
    #add a repo and set it to default one if set.
    #
    if [ -z ${min_argu_2} ]; then
        print -u2 "\n$0: Third argument can not be null..."
        exit 1
    fi      
    publisher_name=${min_argu_1}
    publisher_url=${min_argu_2}
    pfexec pkg set-publisher -O ${publisher_url} ${publisher_name} \
        2>>$err_log 1>&2
    if [ $? -ne 0 ]; then
        print -u2 "$0: Error found when adding repo: "
        print -u2 "${publisher_name} ${publisher_url}"
        exit 1
    fi
}

#
# Modify the existing publisher on the system via
# pkg set-publisher and pkg unset-publisher.
#
function modify
{
    #
    #modify a repo and set it to default one if set.
    #
    if [ -z ${min_argu_2} ]; then
        print -u2 "\n$0: Third argument can not be null..."
        exit 1
    fi      
    publisher_name=${min_argu_1}
    publisher_url=${min_argu_2}

     LC_ALL="C" pfexec pkg publisher ${publisher_name} > \
        /tmp/spe_repo_temp_store 2>>$err_log


    origin_uri=`cat /tmp/spe_repo_temp_store | grep "Origin URI" | \
                nawk -F ": " '{ print $2 }' 2>>$err_log`

    mirror_uris=`cat /tmp/spe_repo_temp_store | grep "Mirror URI" | \
                nawk -F ": " '{ print $2 }' 2>>$err_log`

    store_repo=" -O "${origin_uri}
    extra_repo=" "
    unset_extra_repo=" "

    for mirror_uri in ${mirror_uris}
    do
        extra_repo=${extra_repo}" -m "${mirror_uri}
        unset_extra_repo=${unset_extra_repo}" -M "${mirror_uri}
    done
    
    extra_repo=${extra_repo}" "${publisher_name}

    pfexec pkg unset-publisher ${publisher_name} 2>>/dev/null 1>&2
    if [ $? -ne 0 ]; then
        print -u2 "Warning: Can not remove repo ${publisher_name}"

        pfexec pkg set-publisher -O ${publisher_url} \
                                    ${unset_extra_repo} \
                                    ${publisher_name} \
                                    2>>$err_log 1>&2
        if [ $? -ne 0 ]; then
            print -u2 "$0: Error found when adding repo:"
            print -u2 "${publisher_name} ${publisher_url}"
            exit 1
        else
            echo ${store_repo} > /tmp/spe_repo_store
            echo ${extra_repo} >> /tmp/spe_repo_store
        fi
    else
        echo ${store_repo} > /tmp/spe_repo_store
        echo ${extra_repo} >> /tmp/spe_repo_store
    fi
}

#
# Restore the original publisher on the system
#
function restore
{
    pfexec pkg set-publisher ${min_argu_1} ${min_argu_2} \
        2>>$err_log 1>&2
    if [ $? -ne 0 ]; then
        print -u2 "$0: Error found when restoring repo!"
        exit 1
    fi
}

function clean_up
{
    {
        rm -f  /tmp/repo_temp_store /tmp/repo_default_store \
               /tmp/repo_spe_store \
               /tmp/spe_repo_temp_store /tmp/pkg_candi
    } >/dev/null 2>&1
}


#Main()

PATH=/usr/bin:/usr/sbin:$PATH; export PATH
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/ddu/lib; export LD_LIBRARY_PATH

trap 'clean_up;exit 10' KILL INT
trap 'clean_up' EXIT


#
# Confirm the correct number of commnad line argument
#
if (( $# < 2 )) || (( $# > 3 )); then
    print -u2 "\n$0: Wrong number of arguments provided..."
    exit 1
fi

if [ -z $1 ]; then
    print -u2 "\n$0: First argument can not be null..."
    exit 1
fi

if [ -z $2 ]; then
    print -u2 "\n$0: Second argument can not be null..."
    exit 1
fi


typeset main_argu=$1
typeset min_argu_1=$2
typeset min_argu_2=$3
typeset repo_list repo_url repo_count
typeset repo_listi repo_urli repo_name pkgname 
typeset depend_str pkg_ver pkgcondidate pakcage_found
typeset index
typeset  err_log=/tmp/ddu_err.log

#
# Copy /var/pkg to /tmp if booted off a ramdisk
# Needed by pkg utility so it can expand its bootkeeping files in swap space.
#
if [ -x /usr/lib/install/live_img_pkg5_prep ] ; then
    pfexec /usr/lib/install/live_img_pkg5_prep 2>>$err_log
    if [ $? != 0 ]; then
        print -u2 "Error executing: /usr/lib/install/live_img_pkg5_prep."
        exit 1
    fi

fi

case ${main_argu} in
list)   list;;
search) search;;
add)    add;;
modify) modify;;
restore) restore;;
*)      print -u2 "\n$0: ${main_argu} is not valid"
        exit 1;;
esac
