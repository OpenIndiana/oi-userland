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
# Copyright 1998 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#

# The initial machine wide defaults for csh.

if ( $?TERM == 0 ) then
	if { /bin/i386 } then
		setenv TERM sun-color
	else
		setenv TERM sun
	endif
else
	if ( $TERM == "" ) then
		if { /bin/i386 } then
			setenv TERM sun-color
		else
			setenv TERM sun
		endif
	endif
endif

if (! -e .hushlogin ) then
	/usr/sbin/quota
	/bin/cat -s /etc/motd
	/bin/mail -E
	switch ( $status )
	case 0: 
		echo "You have new mail."
		breaksw;
	case 2: 
		echo "You have mail."
		breaksw;
	endsw
endif

if ( -d /etc/profile.d && ! -f "${HOME}/.limited_profile" ) then
	if ($?nonomatch) then 
		set old=$nonomatch
	else
		unset old
	endif
	set nonomatch=1
	foreach file ( /etc/profile.d/*.csh )
		if ( "$file" == "/etc/profile.d/*.csh" ) then
			break
		endif
		if ( -f "$file" && -r "$file" ) then
			source "$file"
		endif
	end
	if ($?old) then
		set nonomatch="$old"
		unset old
	else 
		unset nonomatch
	endif
	unset file
endif
