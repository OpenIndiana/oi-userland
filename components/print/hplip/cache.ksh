#!/usr/bin/ksh
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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

PPDSRC=${PPDSRC:-"${VER}/share/ppd"}

MODEL="ModelName"
NICK="NickName"
SED="/usr/bin/sed"

if [ -f ${CACHE} ];
then
	/bin/rm ${CACHE}
fi

#
# build a ppdcache for the hpijs PPD files
#
cd ${PPDSRC}
for i in `/bin/ls`
do
  cd $i
  for j in `/bin/ls`
  do
	case "$j" in
	*.gz)
		SRCFILE=/tmp/ppd.$$
		gzcat $j >${SRCFILE}
		PPDFILE="${IPATH}${i}/${j}"
		;;
	*)
		SRCFILE=$j
		PPDFILE="${IPATH}${i}/${j}.gz"
		;;
	esac

	/usr/bin/grep $SRCFILE ${DONOTINSTALL} > /dev/null
	if [ $? = 1 ];
	then
	  MANU=$i
	  MODEL=`/usr/bin/grep "*ModelName:" $SRCFILE | /usr/bin/cut -d '"' -f2`
	  NICKN=`/usr/bin/grep "*NickName:" $SRCFILE | /usr/bin/cut -d '"' -f2`
	  for k in ${MODEL}
	  do
	    # change / to \/ for sed
	    typeset i_clean=$(echo $k | ${SED} -e 's/\//\\\//g')
	    NICKN=$(echo $NICKN | ${SED} -e "s/$i_clean//"  | ${SED} -e "s/^ //")
	  done

	  echo ${MANU}:${MODEL}:${NICKN}:::${PPDFILE} >> ${CACHE}
	fi
  done
  cd ..

done
