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
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		mpc
COMPONENT_VERSION=	0.9
COMPONENT_PROJECT_URL=	http://www.multiprecision.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:fd3efe422f0d454592059e80f2c00d1a2e381bf2beda424c5094abd4deb049ac
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)mpc/download/$(COMPONENT_ARCHIVE)

TPNO=			4706

TEST_TARGET= install $(TEST_32_and_64)
# Add install dependency when system-test target is implemented.
include $(WS_MAKE_RULES)/common.mk

export SHELL
SHELL=$(BINDIR)/sh

CFLAGS +=		`pkg-config --cflags libmpfr`

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--disable-static

COMPONENT_TEST_DIR =		$(BUILD_DIR)/$(MACH$(BITS))/tests

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/mpfr
REQUIRED_PACKAGES += system/library/math
