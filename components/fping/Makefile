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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		fping
COMPONENT_VERSION=	3.16
COMPONENT_PROJECT_URL=	http://www.fping.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:2f753094e4df3cdb1d99be1687c0fb7d2f14c0d526ebf03158c8c5519bc78f54
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)dist/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	834

TPNO=			34404

# Deliver 'sbin' binaries to 'bin'.
CONFIGURE_SBINDIR.64= $(CONFIGURE_BINDIR.64)

CFLAGS +=		$(XPG6MODE)

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION =  \
        ($(CLONEY) $(SOURCE_DIR) $(@D))
