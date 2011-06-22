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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

#
# Description: wrapper to emulate the GNU echo (gecho)
#
# Options from the man page for GNU echo ...
#
#    Echo the STRING(s) to standard output.
#
#    -n   do not output the trailing newline
#
#    -e   enable interpretation of the backslash-escaped  characters listed
#         below:
#              the character whose ASCII code is NNN (octal)
#                   \h|120u+0ubackslash
#                   alert (BEL)
#                   backspace
#                   suppress trailing newline
#                   form feed
#                   new line
#                   carriage return
#                   horizontal tab
#                   vertical tab
#

nflag=0
eflag=0

while getopts en name
do
  case $name in
    n) nflag=1;;
    e) eflag=1;;
    ?) printf "Usage: %s: [-e] [-n] string\n"  $0
       exit 2;;
  esac
done

shift $(($OPTIND - 1))

if [ ${nflag} -ne 1 ]
then
  exec /usr/bin/echo "$*"
else
  exec /usr/bin/echo "$*\c"
fi

exit 1
