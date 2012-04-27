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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		imap
COMPONENT_VERSION=	2007e
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:4b1137b87249782496ec3eeacaf83bbf09312a7d2ae3aead262179041b55565f
#
# Firefox can download this:
#	ftp://ftp.cac.washington.edu/imap/$(COMPONENT_ARCHIVE)
# but our downloader cannot.  Proxy issue?
COMPONENT_ARCHIVE_URL=	$(EXTERNAL_ARCHIVE_MIRROR)/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

CFLAGS += $(CPP_LARGEFILES)
# enable legacy stdio prototypes
# 7050600 sfw doesn't build on 166
CFLAGS += -D__USE_LEGACY_PROTOTYPES__
COMPONENT_BUILD_TARGETS = soc c-client
COMPONENT_POST_BUILD_ACTION = ( \
	$(MV) $(BUILD_DIR_32)/c-client/c-client.a \
		$(BUILD_DIR_32)/c-client/libc-client.a )
ENV += MAKE="$(GMAKE)"
ENV += CC="$(CC)"
ENV += CFLAGS="$(CFLAGS)"

# common targets
build:		$(BUILD_32)

# no install target
install:	build

test:		$(NO_TESTS)

publish:	build

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
