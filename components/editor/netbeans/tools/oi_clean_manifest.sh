#!/usr/bin/env bash

# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

# (C)Copyright 2025, Benny Lyons



# Remove files and directories
rm_lines_with_endings="\.exe \.dll \.so \.a \.sl"
rm_dirs="Linux-x86 Linux-aarch64 Linux-sparc_64 MacOSX-arm_64 MacOSX-x86 SunOS-sparc_64 Windows-x86"

help()
{
    cat<<EOF
    Usage: $0 <options> 

    Script to assist in developing an IPS package
    for OpenIndiana Netbeans.

    While the ultimate goal of generating an OI package
    is to produce a package manifest, i.e., mypackage.p5m,
    it is usually automagicallly produced using tools.
    A prototype manifest file is produced after running
        gmake sample-manifest
    This must _always_ be manually handcrafted and carefully
    edited towards producing the final manifest.

    One manual editing task is to remove static libraries,
    dynamic libraries, ... For a large project this can be
    tedious and error prone, especially if the process has
    to be repeated several times. This scipt alleviated the
    labour somewhat while developing a package.

    WARNING

    Always run from the directory containg the manifest.
    
    gmake sample-manifest

    cp ./manifest/sample-manifest.p5m ./your_package_name.p5m
    cp ./your_package_name.p5m ./whatever.p5m
    ./tools/oi_clean_manifest.sh ./your_package_name.p5m

    If ok, there is no output. Your package manifest is updated.

    Then check: diff   your_package_name.p5m whatever.p5m
    Carefully examine.

    Re-running this script more than once should produce no output.


    OPTIONS
    -h [--help] help, this text
    -m <manifest_filename>
       DEFAULT: <top_dir>.p5m

    PROBLEMS

    EXAMPLES
    $0 
 
EOF
}


main()
{
        opts_all="hm:"
        
        while  getopts ${opts_all} opt; do
                case ${opt} in
			h)     
				help
				exit 0
                                ;;
                        m)
                                opt_manifest=$OPTARG
                                ;;

                       \?)
                                echo "ERROR: Don't know this option"
                                echo "       For more help, try $0 -h"
                                exit 1
                                ;;
                        :)
                                echo "       This option requires an argument, none given"
                                echo "       For more help, try $0 -h"
                                ;;
                esac
	done


        if [ -z "$opt_manifest" ]; then
                manifest_file=${PWD##*/}.p5m
        else
                manifest_file="$opt_manifest"
        fi
        if [ ! -f "$manifest_file" ]; then
                echo "ERROR: cannot find manifest file: "$manifest_file
                exit 1
        fi

        
        for lineending in $rm_lines_with_endings; do
                sed -i "/${lineending}$/d" $manifest_file
        done
        for word in $rm_dirs; do
                sed -i "/${word}/d" $manifest_file 
        done
}
main "$@"


