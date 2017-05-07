#! /usr/bin/python2.7
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
"""
parse p5i file
"""
CURRENT_P5I_VERSION = 1
import simplejson as json
import commands
import sys

FILEOBJ = sys.argv[1]


STATUS, OUTPUT = commands.getstatusoutput('/usr/bin/cat %s' %str(FILEOBJ))

try:
    DUMP_STRUCT = json.loads(OUTPUT)
except AttributeError:
    pass


try:
    VER = int(DUMP_STRUCT["version"])
except AttributeError:
    pass

if VER > CURRENT_P5I_VERSION:
    print "Version error"
    sys.exit(1)

RESULT = []
REPO = []

try:
    PLIST = DUMP_STRUCT.get("publishers", [])
    for p in PLIST:
        alias = p.get("alias", None)
        prefix = p.get("name", None)

        if not prefix:
            prefix = "Unknown"

        pkglist = p.get("packages", [])
        RESULT.append((prefix, pkglist))

        for r in p.get("repositories", []):
            rargs = {}
            for prop in ("collection_type",
                         "description",
                         "name",
                         "refresh_seconds",
                         "registration_uri"):
                val = r.get(prop, None)
                if val is None or val == "None":
                    continue
                rargs[prop] = val


            for prop in ("legal_uris",
                         "mirrors",
                         "origins",
                         "related_uris"):
                val = r.get(prop, [])
                if not isinstance(val, list):
                    continue
                rargs[prop] = val


            if rargs.get("origins", None):
                REPO.append(rargs.get("origins", None))

    PKGLIST = DUMP_STRUCT.get("packages", [])
    if PKGLIST:
        RESULT.append((None, PKGLIST))

except AttributeError:
    print "Get publishers error!"
    sys.exit(1)

INDEX0 = len(RESULT)
INDEX1 = len(REPO)


if INDEX0 > 0 and INDEX1 > 0:
    for item in RESULT:
        item_key0 = item[0]
        item_key1 = item[1]
        for item_key_11 in item_key1:
            for repo_item in REPO:
                print "%s\t%s\t%s" % (item_key0, item_key_11, repo_item[0])
