#!/bin/bash
#
# Script for setting up the shell environment for using the Desktop CBE
#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License, Version 1.0 only
# (the "License").  You may not use this file except in compliance
# with the License.
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
# Copyright 2008 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#

init_dt_cbe () {
    test "x$JDS_CBE_ENV_QUIET" != x1  && \
	echo "Desktop CBE version 1.8.0"

    myarch=`uname -p`
    if [ $myarch = "i386" ]; then
	myarch=x86
    fi

    save_IFS="$IFS"
    IFS=" 
"
    ENV_SET=`env | grep '^[a-zA-Z0-9_]*=' | cut -f1 -d=`
    if [ "x$ZSH_VERSION" != x ]; then
	set -o sh_word_split
    else
	for var in $ENV_SET; do
	    case $var in
		PS1|PS2|HZ|TERM|SHELL|OLDPWD|PATH|MAIL|PWD|TZ|SHLVL|HOME|LOGNAME|PRINTER|HOSTNAME|_|CC|CXX|EDITOR|SSH_*|DISPLAY|LESS*|LS_COLORS|LS_OPTIONS|TERMINFO|PAGER|MANPATH|VISUAL|http_proxy|https_proxy|ftp_proxy|XAUTHORITY|CVSROOT|CVS_RSH|DBUS_*|SESSION_MANAGER|JDS_CBE_ENV_QUIET)
		;;
	    *)
		test "x$JDS_CBE_ENV_QUIET" != x1 && echo Unsetting $var
                unset $var
                ;;
            esac
        done
    fi

    IFS="$save_IFS"
    CBE_PREFIX=/opt/dtbld

    if [ "x$1" != x ]; then
	if [ -f "$CBE_PREFIX/lib/cbe-env/$1" ]; then
	    . "$CBE_PREFIX/lib/cbe-env/$1"
	    export CC
	    export CXX
	else
	    echo "ERROR: Unknown CBE environment: $1" 1>&2
	    echo
	    echo "Valid choices are: "
	    /bin/ls -l "$CBE_PREFIX/lib/cbe-env" | cut -c54- | /bin/sed -e 's/ /	/'
	    echo
	    return 1
	fi
    else
	if [ -f "$CBE_PREFIX/lib/cbe-env/default" ]; then
	    . "$CBE_PREFIX/lib/cbe-env/default"
	    export CC
	    export CXX
	else
	    echo "ERROR: Default CBE environment missing" 1>&2
	    return 1
	fi
    fi

    # backward compat with old JDS CBEs:
    CC32="$CC"
    CC64="$CC"
    CXX32="$CXX"
    CXX64="$CXX"
    export CC32 CC64 CXX32 CXX64

    if [ "x$JDS_CBE_ENV_QUIET" != x1 ]; then
	echo Using CC=$CC
	echo Using CXX=$CXX
    fi

    CCDIR=`dirname $CC`
    if [ $CCDIR != /usr/bin ]; then
	PATH="$CBE_PREFIX/bin:$CCDIR:/usr/ccs/bin:/usr/gnu/bin:/usr/bin:/usr/sbin:/bin:/usr/sfw/bin"
    else
	PATH="$CBE_PREFIX/bin:/usr/ccs/bin:/usr/gnu/bin:/usr/bin:/usr/sbin:/bin:/usr/sfw/bin"
    fi

    test "x$JDS_CBE_ENV_QUIET" != x1  && \
	echo Setting PATH=$PATH
    export PATH
    
    CONFIG_SHELL="/bin/bash"
    test "x$JDS_CBE_ENV_QUIET" != x1  && \
	echo Setting CONFIG_SHELL=$CONFIG_SHELL
    export CONFIG_SHELL

    MAKESHELL="/bin/bash"
    test "x$JDS_CBE_ENV_QUIET" != x1  && \
	echo Setting MAKESHELL=$MAKESHELL
    export MAKESHELL

    MAKE="$CBE_PREFIX/bin/make"
    test "x$JDS_CBE_ENV_QUIET" != x1  && \
	echo Setting MAKE=$MAKE
    export MAKE

    M4="$CBE_PREFIX/bin/m4"
    test "x$JDS_CBE_ENV_QUIET" != x1  && \
	echo Setting M4=$M4
    export M4

    return 0
}
