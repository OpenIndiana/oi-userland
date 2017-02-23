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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		liblogging
COMPONENT_VERSION=	1.0.5
COMPONENT_PROJECT_URL=	http://www.liblogging.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:310dc1691279b7a669d383581fe4b0babdc7bf75c9b54a24e51e60428624890b
COMPONENT_ARCHIVE_URL=	\
    http://download.openpkg.org/components/cache/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
# The original download site seems to be broken, it is not possible to
# download the archive from there
#    http://download.rsyslog.com/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
# The checksum of the archive corresponds to what is written on liblogging.org
COMPONENT_BUGDB=	service/rsyslog
TPNO=			27183
COMPONENT_ANITYA_ID=	1654

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Means build only stdlog
CONFIGURE_OPTIONS +=    --disable-journal

# There are built man pages in the tarball, which we shall patch. Making them
# here would require python-docutils.
CONFIGURE_OPTIONS +=	--disable-man-pages
