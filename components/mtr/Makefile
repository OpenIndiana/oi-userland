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
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		mtr
COMPONENT_VERSION=	0.86
COMPONENT_PROJECT_URL=	http://www.bitwizard.nl/mtr/
COMPONENT_ARCHIVE_HASH=	\
    sha256:7912f049f9506748913e2866068b7f95b11a4e0a855322120b456c46ac9eb763
COMPONENT_ARCHIVE_URL=	https://github.com/traviscross/mtr/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ANITYA_ID=	2029

TPNO=			18130

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_SBINDIR.64 =		$(CONFIGURE_PREFIX)/bin
CONFIGURE_OPTIONS  +=		--without-gtk
CONFIGURE_OPTIONS  +=		--without-ipinfo

COMPONENT_PRE_CONFIGURE_ACTION += (cd $(SOURCE_DIR); ./bootstrap.sh)

REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library/math
