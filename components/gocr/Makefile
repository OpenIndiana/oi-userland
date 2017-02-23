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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gocr
COMPONENT_VERSION=	0.50
COMPONENT_PROJECT_URL=	http://jocr.sourceforge.net/
COMPONENT_ARCHIVE_HASH=	\
    sha256:bc261244f887419cba6d962ec1ad58eefd77176885093c4a43061e7fd565f5b5
COMPONENT_ARCHIVE_URL=	http://www-e.uni-magdeburg.de/jschulen/ocr/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	1225

TPNO=			21551

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Fix 64-bit linking done via compiler.
LDFLAGS += $(CC_BITS)

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/math
