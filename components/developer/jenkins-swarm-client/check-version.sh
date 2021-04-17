#!/bin/sh

# Find the latest (tarball) release under original site
#
# Copyright 2016-2021 Jim Klimov
#

BASE_URL="https://repo.jenkins-ci.org/releases/org/jenkins-ci/plugins/swarm-client"
DL_PAGE_URL="https://plugins.jenkins.io/swarm/#releases"

echo "=== Checking latest numbered release under $BASE_URL..."
UPSTREAM_VERSION="`wget -q -O - "$BASE_URL" 2>/dev/null | egrep 'href="[0-9]*\.[0-9]*/*"' | sed 's,^.*a href="\([0-9]*\.[0-9]*\)/*".*,\1,' | /usr/gnu/bin/sort -V | tail -1`" \
    && [ -n "$UPSTREAM_VERSION" ] && echo "Latest UPSTREAM_VERSION   = $UPSTREAM_VERSION" \
    || echo "WARNING: Could not fetch an UPSTREAM_VERSION, check manually at $DL_PAGE_URL or $BASE_URL" >&2

#UPSTREAM_CHECKSUM="`wget -O - "$BASE_URL/$UPSTREAM_VERSION/swarm-client-${UPSTREAM_VERSION}.jar.sha256" 2>/dev/null | awk '{print $1}'`" \
#    && [ -n "$UPSTREAM_CHECKSUM" ] && echo "Latest SHA256SUM = sha256:$UPSTREAM_CHECKSUM" \
#    || echo "WARNING: Could not fetch an UPSTREAM_CHECKSUM" >&2

MF="`dirname $0`/Makefile"
echo "=== Data in current ${MF}:"
egrep '(^[\t\ ]*(COMPONENT_VERSION.*=|sha256:))' "${MF}"
MAKEFILE_VERSION="`egrep 'COMPONENT_VERSION.*=.*[0-9]' ${MF} | sed 's,^.*[ \"\t]\([0-9][0-9.]*\)[^0-9.]*.*$,\1,'`"
MAKEFILE_CHECKSUM="`grep 'sha256:' ${MF} | sed 's,^.*sha256:,,'`"

UPTODATE=false
if [ "$MAKEFILE_VERSION" = "$UPSTREAM_VERSION" ] ; then
    echo "=== MAKEFILE_VERSION matches the UPSTREAM_VERSION currently"
    UPTODATE=true
else
    echo "WARNING: No checksum is served currently by remote source. Please:"
    echo "    update the Makefile for new version once, then"
    echo "    run 'gmake fetch' to download the new version to package, and"
    echo "    update the Makefile again with that reported 'actual' checksum"
fi

#if [ "$MAKEFILE_CHECKSUM" = "$UPSTREAM_CHECKSUM" ] ; then
#    echo "=== MAKEFILE_CHECKSUM matches the UPSTREAM_CHECKSUM currently"
#    UPTODATE=true
#fi

if ! $UPTODATE ; then
    echo "=== Please edit the Makefile and commit like this:"
    echo "    git add -p Makefile; git commit -m 'Bump jenkins-swarm-client to v${UPSTREAM_VERSION}'"
else
    echo "=== Nothing to update at this time"
fi
