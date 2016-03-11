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
# Copyright (c) 2012, 2016, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		xz
COMPONENT_VERSION=	5.2.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://tukaani.org/xz/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:73df4d5d34f0468bd57d09f2d8af363e95ed6cc3a4a86129d2f2c366259902a2
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/xz

TPNO=			27216

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS +=		CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=		--bindir=$(USRBINDIR)

COMPONENT_TEST_DIR =		$(@D)/tests

# Master test results are the same for 32-bit and 64-bit, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# The additional xz specific set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^.*$(CC).*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*source=.*libtool=no.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*DEPDIR=.deps.*$$|XXX_CC_XXX|g" ' \
	'-e "/^XXX_CC_XXX$$/d" '

# Needed to build the test programs.
COMPONENT_PRE_SYSTEM_TEST_ACTION += \
	(cd $(@D)/src/liblzma ; $(GMAKE) liblzma.la )

COMPONENT_SYSTEM_TEST_DIR =	$(@D)/tests
COMPONENT_SYSTEM_TEST_ENV +=	XZ_SCRIPT=/usr/bin/xz
COMPONENT_SYSTEM_TEST_ENV +=	XZDEC_SCRIPT=/usr/bin/xzdec
COMPONENT_SYSTEM_TEST_ENV +=	XZDIFF_SCRIPT=/usr/bin/xzdiff
COMPONENT_SYSTEM_TEST_ENV +=	XZGREP_SCRIPT=/usr/bin/xzgrep

ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_32_and_64)

build:		$(BUILD_32_and_64)

include $(WS_MAKE_RULES)/shared-targets.mk

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

system-test:    configure $(SYSTEM_TEST_32_and_64)

REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/crypto
