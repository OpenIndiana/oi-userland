#!/bin/bash
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
# Copyright (c) 2008, 2011, Oracle and/or its affiliates. All rights reserved.
#

# Find the PPD files delivered by foomatic that Solaris does not support.
# There are two reasons for non-support:
#
#	1. license/patent issues with the driver (listed in file nolicense). These
#	   files are removed and not delivered
#	2. The driver used by the PPD file must be brought downand compiled and
#	   Solaris has not chosen to do so. In that case the PPD file is delivered,
#	   but not included in the generated cache file.
#
# The unsupported PPD file should be listed in $BUILD_DIR/ppdunsupported for
# review. The catchall file, ppdsnomatch, should be empty. If not, a new
# case is needed in this script. The other files are there for debugging
# purposes.

# Notes:
#	drivers come in several flavors: gs built in, gs uniprint, postscript,
#	hpijs, and then the several other drivers.
# Drivers are noted in many PPD files with driverType. To sort these, look
# for:	driverType G/GhostScript built-in:
#	driverType U/GhostScript Uniprint:
#	driverType F/Filter: "" 
# Drivers are also noted in the name of the ppd file. This is used
# to cull out postscript, hpijs, and pxlmono . These do not reliably
# use driverType. note: pxlmono driver is a gs built-in but many of the
# ppd files that use this driver do not utilize the driverType line.
# driverType I/IJS: "" is not reliable for hpijs as not used in many ppds.
 
# driverType F/Filter: "" denotes ppd files that use GhostScript and
# then pipe that output to one or more other drivers. These will only be 
# supported if Solaris compiles and delivers these drivers.

# Make sure that there are no undefined variables
set -ue

# Sanitize PATH
PATH=/usr/bin:/bin

if [ -z "${1-}" ] || [ -z "${2-}" ] ||
	[ -z "${3-}" ] || [ -z "${4-}" ]; then
	echo "Usage: $0 build-dir tree-of-ppds cache-file nolicense-file"
	exit 1
fi

# Build directory
BUILD_DIR="$1"
# Where PPD files are located
BASE="$2"
# Cache file to be created
CACHE="$3"
# File listing PPDs with no/invalid license
NOLICENSE="$4"
# Base install path for PPD files
IPATH=/usr/share/ppd/SUNWfoomatic

# Script will fail if set
FAIL_LATER=""

mkdir -p "$( dirname "$CACHE" )"
/bin/rm -f ${BUILD_DIR}/ppdunsupported \
		${BUILD_DIR}/ppdsupported \
		${BUILD_DIR}/ppdsnomatch \
		"$CACHE"

# files which should be included in the cache


#-----
##
## add_to_cache
##
## That means the PPD will be included in ## generated cache. Function uses
## global variables $i and $j. Function expects that we are already in
## directory $i
##
#-----
add_to_cache() {
	typeset SRCFILE
	typeset PPDFILE

	# Add the file to the cache
	case "$j" in
		*.gz)
			SRCFILE=${BUILD_DIR}/ppd.$$
			gzcat $BASE/$i/$j >${SRCFILE}
			PPDFILE="${IPATH}/$i/$j"
			;;
		*)
			SRCFILE=$BASE/$i/$j
			PPDFILE="${IPATH}/$i/$j.gz"
			;;
	esac

	typeset MANU=$i
	typeset MODEL
	MODEL=`grep "*ModelName:" $SRCFILE | cut -d '"' -f2`
	typeset NICKN
	NICKN=`grep "*NickName:" $SRCFILE | cut -d '"' -f2`

	typeset k
	for k in ${MODEL}
	do
		# change / to \/ for sed
		typeset i_clean=$(echo $k | sed -e 's/\//\\\//g')
		NICKN=$( echo $NICKN |
			sed -e "s/$i_clean//" | sed -e "s/^ //" )
	done

	echo ${MANU}:${MODEL}:${NICKN}:::${PPDFILE} >> ${CACHE}
}


#-----
##
## supported
##
## process PPD supported file.
##
#-----
supported() {
	echo "$i/$j" >> ${BUILD_DIR}/ppdsupported
	add_to_cache
}

#-----
##
## unsupported
##
## Handle PPD files NOT supported and thus included in the cache
##
#-----
unsupported() {
	echo "$i/$j - $1" >> ${BUILD_DIR}/ppdunsupported
}

#-----
##
## nomatch
##
## Handle PPD files for which we don't know how to decide whether it's
## supported or not
##
#-----
nomatch() {
	echo "$i/$j" >> ${BUILD_DIR}/ppdsnomatch
	echo "file '$i/$j' did not match any rule"
	FAIL_LATER=1
}

# Go to directory with PPD files
cd "$BASE"

# Walk through all the PPD files available
for i in *
do
	cd "$i"
		for j in *
		do
			# First detect all files listed in the "nolicense" file
			if ls $j | /usr/xpg4/bin/grep -f "$NOLICENSE" >/dev/null ; then
				echo "Removing file '$j' because it is listed in 'nolicense' file"
				/bin/rm $j
				continue
			fi

			# The following cases pull out supported drivers
			if ls $j | grep Postscript > /dev/null; then
				supported
				continue
			fi

			if grep "driverType G/GhostScript built-in: " $j >> /dev/null; then
				supported
				continue
			fi

			if grep "driverType U/GhostScript Uniprint: " $j >> /dev/null; then
				supported
				continue
			fi

			# HPLIP (hpijs) supplies it's own Foomatic PPD files
			if ls $j | grep hpijs > /dev/null; then
				unsupported 'hpijs'
				continue
			fi

			if ls $j | grep pxlmono > /dev/null; then
				supported 'pxlmono'
				continue
			fi

			# These are the unsupported printers unless
			# we build and deliver the drivers
			if grep "driverType F/Filter: """ $j >> /dev/null; then
				unsupported 'driverType F/Filter'
				continue
			fi

			# No match : this should not happen
			nomatch
		done
	cd ..
done

if [ -n "$FAIL_LATER" ]; then
	exit 1
else
	exit 0
fi
