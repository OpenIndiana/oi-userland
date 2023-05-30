#!/bin/sh

# Find the latest (tarball) release under original site
#
# Copyright 2016-2023 Jim Klimov
#

BASE_URL="https://get.jenkins.io/war-stable/"
DL_PAGE_URL="https://www.jenkins.io/download/"

echo "=== Checking latest numbered release under $BASE_URL..."
UPSTREAM_VERSION="`wget -q -O - "$BASE_URL" 2>/dev/null | egrep 'href="[0-9]*\.[0-9]*\.[0-9]*/"' | grep -vw latest | sed 's,^.*a href="\([0-9]*\.[0-9]*\.[0-9]*\)/*".*,\1,' | sort -t. -k1n,1n -k2n,2n -k3n,3n | tail -1`" \
    && [ -n "$UPSTREAM_VERSION" ] && echo "Latest UPSTREAM_VERSION   = $UPSTREAM_VERSION" \
    || echo "WARNING: Could not fetch an UPSTREAM_VERSION, check manually at $DL_PAGE_URL " >&2

UPSTREAM_CHECKSUM="`wget -O - "$BASE_URL/latest/jenkins.war.sha256" 2>/dev/null | awk '{print $1}'`" \
    && [ -n "$UPSTREAM_CHECKSUM" ] && echo "Latest SHA256SUM = sha256:$UPSTREAM_CHECKSUM" \
    || echo "WARNING: Could not fetch an UPSTREAM_CHECKSUM" >&2

MF="`dirname $0`/Makefile"
echo "=== Data in current ${MF}:"
egrep '(^[\t\ ]*(COMPONENT_[A-Z]*_VERSION.*=|JENKINS_RELEASE.*=)|sha256:)' "${MF}"
MAKEFILE_CHECKSUM="`grep 'sha256:' ${MF} | sed 's,^.*sha256:,,'`"

if [ "$MAKEFILE_CHECKSUM" = "$UPSTREAM_CHECKSUM" ] ; then
    echo "=== MAKEFILE_CHECKSUM matches the UPSTREAM_CHECKSUM currently"
fi

echo "=== Please edit the Makefile and commit like this (if needed):"
echo "    git add -p Makefile; git commit -m 'Bump jenkins-core-lts to v${UPSTREAM_VERSION}'"
