#!/bin/sh

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
# Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
#

if [ -z "$PROTO_DOC" ]; then
    MACH=`/usr/bin/uname -p`
    PROTO_DOC=`pwd`/build/prototype/$MACH/usr/share/lib/java/javadoc
fi

# Output this copyright
cat $0 | head -27 | tail -25

# Output pkg manifest
cat <<EOF
set name=info.classification value="org.opensolaris.category.2008:Applications/Configuration and Preferences"
set name=pkg.fmri value=pkg:/system/management/visual-panels/doc@\$(IPS_COMPONENT_VERSION),\$(BUILD_VERSION)
set name=pkg.summary value="Visual Panels - API Documentation"
set name=org.opensolaris.consolidation value=\$(CONSOLIDATION)
set name=org.opensolaris.arc-caseid value=LSARC/2007/392

license ../vpanels.copyright license=Oracle

dir path=usr
dir path=usr/share
dir path=usr/share/lib
dir path=usr/share/lib/java
EOF

# pkgsend doesn't have any way to specify limits on the files it processes, so
# just grep for those in $PROTO_DOC
echo "$PROTO_DOC" | sed 's#/\(usr/\)# \1#' | read base docprefix
pkgsend generate "$base" | ggrep -F "path=$docprefix" | sort |
awk -F' ' '{
    if ($1=="dir")
    {
        print $1" "$5

    } else if ($1=="file")
    {
        print $1" "$6
    }
}'

exit 0
