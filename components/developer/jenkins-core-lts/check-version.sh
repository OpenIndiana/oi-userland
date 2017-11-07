#!/bin/sh

# Find the latest (tarball) release under original site
#
# Copyright 2016-2017 Jim Klimov
#

BASE_URL="http://mirrors.jenkins.io/war-stable/"

echo "=== Checking latest numbered release under $BASE_URL..."
VERSION="`wget -q -O - "$BASE_URL" 2>/dev/null | egrep 'DIR.*[0-9]*\.[0-9]*' | grep -vw latest | tail -1 | sed 's,^.*a href="\([0-9]*\.[0-9]*\.[0-9]*\)/*".*,\1,'`" \
    && [ -n "$VERSION" ] && echo "Latest VERSION   = $VERSION" \
    || echo "WARNING: Could not fetch a VERSION" >&2

CHECKSUM="`wget -O - "$BASE_URL/latest/jenkins.war.sha256" 2>/dev/null`" \
    && [ -n "$CHECKSUM" ] && echo "Latest SHA256SUM = sha256:$CHECKSUM" \
    || echo "WARNING: Could not fetch a CHECKSUM" >&2

echo "=== Data in current `dirname $0`/Makefile:"
egrep '(^[\t\ ]*(COMPONENT_[A-Z]*_VERSION.*=|JENKINS_RELEASE.*=)|sha256:)' "`dirname $0`/Makefile"