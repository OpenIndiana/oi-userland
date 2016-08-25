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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         xorriso
COMPONENT_VERSION=      0.6.0
COMPONENT_PROJECT_URL=  http://scdbackup.sourceforge.net/xorriso/
COMPONENT_ARCHIVE_HASH=	\
    sha256:1f26880eaacf7bd806520a458963d2374ad6bf90353e08ed0de271b6d45c5b8a
COMPONENT_ARCHIVE_URL=  http://scdbackup.sourceforge.net/$(COMPONENT_ARCHIVE)

TPNO=			3504

CPPFLAGS+=		-I./test

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS  +=           --enable-shared
CONFIGURE_OPTIONS  +=           --disable-static
CONFIGURE_OPTIONS  +=           --sysconfdir=$(ETCDIR)/gnu
CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)

# The tarball for this version already has a config.status file so remove it.
COMPONENT_PREP_ACTION = \
	 (cd $(@D) ; test -f config.status && rm config.status)

REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/zlib
