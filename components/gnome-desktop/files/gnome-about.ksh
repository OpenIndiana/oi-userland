#!/bin/ksh -ph
##
## This script wraps GNOME About, which is called by GNOME Session the first
## time that a user logs in, and does some other iniital login tasks:
## - Creates a launcher on the user's Desktop to open the Solaris Developer
##   Guide start page
## - Launchs Firefox with the start page.
## - For first logon by root launches users-admin tool
## 
##
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
# Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#

##
## Figure out the base installdir
##
BASEDIR="${0%%/bin*}"
if [ -z "$BASEDIR" ]; then
    # /bin tends to be a symbolic link, so follow it and do calc basedir off
    # that.
    DIRNAME=`dirname $0`
    BASEDIR=`cd "$DIRNAME"; sh -c pwd`
    BASEDIR="${BASEDIR%%/bin*}"
fi

##
## Create variables
##
GNOME_ABOUT_BIN="${BASEDIR}/lib/gnome-about"
GCONFTOOL="${BASEDIR}/bin/gconftool-2"
FIREFOX="${BASEDIR}/bin/firefox"
USERS_ADMIN="${BASEDIR}/bin/users-admin" 
XPG4_ID="/usr/xpg4/bin/id"
ID="/usr/bin/id"

GCONF_DEVGUIDE_PROMPT_KEY="/apps/gnome-session/options/sun_extensions/viewed_dev_guide_jds_solaris"
SOLDEVEX_ROOT="${BASEDIR}/share/doc/soldevex/html"
SOLDEVEX_FILE="developer_guide.html"
XDG_APPLICATIONS_DIR="${BASEDIR}/share/applications"
SOLDEVEX_DESKTOP_FILE="devguide.desktop"
USER_DESKTOP_DIR="${HOME}/Desktop" 

##
## Define some utility functions
##

#
# Checks if it's the first time the user is running gnome-about
#
isFirstTime() {
    typeset value=""
    if [ -x "${GCONFTOOL}" ]; then
        value=`${GCONFTOOL} -g "${GCONF_DEVGUIDE_PROMPT_KEY}" 2>/dev/null`
    fi
    test "${value}" != "true"
    return $?
}

markFirstRunDone() {
    if [ -x "${GCONFTOOL}" ]; then
        ${GCONFTOOL} -s -t bool "${GCONF_DEVGUIDE_PROMPT_KEY}" true 2>/dev/null
        return 0
    fi
    return 1
}

#
# Looks for the developer guide HTML file.
#
# NOTE: First checks if a localised version exists, otherwise picks the
# default version.
#
locateHTMLFile() {
    typeset LANG_FILE="${SOLDEVEX_ROOT}/${LANG}/${SOLDEVEX_FILE}"
    typeset DEFAULT_FILE="${SOLDEVEX_ROOT}/${SOLDEVEX_FILE}"
    if [ -r "${LANG_FILE}" ]; then
        echo "${LANG_FILE}"
    elif [ -r "${DEFAULT_FILE}" ]; then
        echo "${DEFAULT_FILE}"
    else
        echo ""
        return 1
    fi
    return 0
}

#
# Attempts to create an launcher on the user's desktop for a pointer to the
# Developer Guide.
#
copyDesktopFile() {
    typeset XDG_DESKTOP_FILE="${XDG_APPLICATIONS_DIR}/${SOLDEVEX_DESKTOP_FILE}" 
    typeset USER_DESKTOP_FILE="${USER_DESKTOP_DIR}/${SOLDEVEX_DESKTOP_FILE}" 

    if [ -r "${XDG_DESKTOP_FILE}" ]; then
        if [ ! -w "${USER_DESKTOP_DIR}" ]; then
            mkdir "${USER_DESKTOP_DIR}" || return 1 # If fails return
        fi
        if [ ! -e "${USER_DESKTOP_FILE}" ]; then
            cp "${XDG_DESKTOP_FILE}" "${USER_DESKTOP_FILE}" || return 1 # If fails return
        fi
    else
        return 1
    fi
    return 0
}

#
# Launch firefox for the given HTML File
#
launchFirefox() {
    if [ -x "${FIREFOX}" -a -n "${1}" ]; then
        ${FIREFOX} "${1}" &     # Needs to be run in the background
    fi
}

#
# Launch UsersAdmin
#
launchUsersAdmin() {
   if [ -x "${USERS_ADMIN}" ]; then
       ${USERS_ADMIN} &     # Needs to be run in the background
   fi
}

#
# Check if the user is NOT root.
#
isNotRootUser() {
    typeset USER_ID
    if [ -x "$XPG4_ID" ]; then
        USER_ID=`${XPG4_ID} -u`
    else
        # Needs a little more work to get the UID.
        USER_ID=`${ID}`
        USER_ID=`expr "${USER_ID}" : "uid=\([0-9]*\)(.*" 2>/dev/null`
    fi
    if [ -n "${USER_ID}" -a "${USER_ID}" -ne 0 ]; then
        return 0
    else
        return 1
    fi
}

## 
## Main
## 

if isFirstTime; then

    # See if we have the Solaris Developers Guide somewhere.
    HTML_FILE=`locateHTMLFile`
    if [ $? -eq 0 ]; then
        # Try copy the Desktop entry over to users Desktop dir.
        copyDesktopFile

        # Now try to launch Firefox with Dev Guide, but not for root
        if isNotRootUser; then
            launchFirefox "${HTML_FILE}"
       else
          launchUsersAdmin
       fi 
    fi
    
    # Now that we've finished, don't forget to remember this.
    markFirstRunDone
fi

# Finally, just run the GNOME About application, with params, if any.
exec ${GNOME_ABOUT_BIN} ${1+"$@"}
