#!/bin/csh
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

if ( ! ${?JDS_CBE_ENV_QUIET} ) set JDS_CBE_ENV_QUIET=0

test "$JDS_CBE_ENV_QUIET" != 1  && \
    echo "Desktop CBE version 1.8.0"

set myarch=`uname -p`
if ( $myarch == "i386" ) set myarch=x86

set vars=`env | grep '^[a-zA-Z0-9_]*=' | cut -f1 -d=`
foreach var ( $vars )
    switch ($var)
    case PS1:
    case PS2:
    case HZ:
    case TERM:
    case SHELL:
    case OLDPWD:
    case PATH:
    case MAIL:
    case PWD:
    case TZ:
    case SHLVL:
    case HOME:
    case LOGNAME:
    case PRINTER:
    case HOST:
    case HOSTNAME:
    case HOSTTYPE:
    case _:
    case CC:
    case CXX:
    case EDITOR:
    case SVN_EDITOR:
    case SSH_*:
    case DISPLAY:
    case LESS*:
    case LS_COLORS:
    case LS_OPTIONS:
    case TERMINFO:
    case PAGER:
    case MANPATH:
    case VISUAL:
    case http_proxy:
    case https_proxy:
    case ftp_proxy:
    case CVSROOT:
    case CVS_RSH:
    case DBUS_*:
    case SESSION_MANAGER:
    case XAUTHORITY:
    case JDS_CBE_ENV_QUIET:
      breaksw
    default:
      test "$JDS_CBE_ENV_QUIET" != 1  && echo Unsetting $var
      unsetenv $var
      breaksw
    endsw
end

set CBE_PREFIX=/opt/dtbld

set invalid_env=no
if ( $#argv >= 1 ) then
    if ( -f "$CBE_PREFIX/lib/cbe-env/$argv[1]" ) then
	eval setenv CC `cat "$CBE_PREFIX/lib/cbe-env/$argv[1]" | grep '^CC=' | cut -f2- -d=`
	eval setenv CXX `cat "$CBE_PREFIX/lib/cbe-env/$argv[1]" | grep '^CXX=' | cut -f2- -d=`
    else
	echo "ERROR: Unknown CBE environment: $argv[1]"
	echo
	echo "Valid choices are: "
	/bin/ls -l "$CBE_PREFIX/lib/cbe-env" | cut -c54- | /bin/sed -e 's/ /	/'
	echo
	set invalid_env=yes
    endif
else
    if ( -f "$CBE_PREFIX/lib/cbe-env/default" ) then
	eval setenv CC `cat "$CBE_PREFIX/lib/cbe-env/default" | grep '^CC=' | cut -f2- -d=`
	eval setenv CXX `cat "$CBE_PREFIX/lib/cbe-env/default" | grep '^CXX=' | cut -f2- -d=`
    else
	echo "ERROR: Default CBE environment missing"
	set invalid_env=yes
    endif
endif

if ( $invalid_env != yes ) then
    # backward compat with old JDS CBEs:
    setenv CC32 "$CC"
    setenv CC64 "$CC"
    setenv CXX32 "$CXX"
    setenv CXX64 "$CXX"

    if ( "$JDS_CBE_ENV_QUIET" != 1 ) then
	echo Using CC=$CC
	echo Using CXX=$CXX
    endif

    set CCDIR=`dirname $CC`
    if ( $CCDIR != "/usr/bin" ) then
	setenv PATH "${CBE_PREFIX}/bin:${CCDIR}:/usr/ccs/bin:/usr/gnu/bin:/usr/bin:/usr/sbin:/bin:/usr/sfw/bin"
    else
	setenv PATH "${CBE_PREFIX}/bin:/usr/ccs/bin:/usr/gnu/bin:/usr/bin:/usr/sbin:/bin:/usr/sfw/bin"
    endif

    test "$JDS_CBE_ENV_QUIET" != 1  && \
	echo Setting PATH=$PATH
endif

setenv CONFIG_SHELL "/bin/bash"
test "$JDS_CBE_ENV_QUIET" != 1  && \
    echo Setting CONFIG_SHELL=$CONFIG_SHELL

setenv MAKESHELL "/bin/bash"
test "$JDS_CBE_ENV_QUIET" != 1  && \
    echo Setting MAKESHELL=$MAKESHELL

setenv MAKE "$CBE_PREFIX/bin/make"
test "$JDS_CBE_ENV_QUIET" != 1  && \
    echo Setting MAKE=$MAKE

setenv M4 "$CBE_PREFIX/bin/m4"
test "$JDS_CBE_ENV_QUIET" != 1  && \
    echo Setting M4=$M4

set bash_opts="--norc --noprofile"
set ksh_opts="-p"
set ksh93_opts="-p"
set csh_opts="-f"
set tcsh_opts="-f"

if ( $?SHELL ) then
    set subshell=${SHELL}
else
    set subshell=/bin/csh
endif

set subshell_name=`basename $subshell`
eval set subshell_opts='"$'${subshell_name}_opts'"'

if ( $?0 ) then
    set mybasename=`basename $0`
else
    set mybasename=/bin/csh
endif

if ( $mybasename == env.csh ) then
    if ( $invalid_env == yes ) then
	exit 1
    endif
    echo Starting subshell $subshell $subshell_opts
    exec $subshell $subshell_opts
endif

# return value when sourcing this script
test $invalid_env != yes
