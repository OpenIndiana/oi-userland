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
# Copyright (c) 2012, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		xz
COMPONENT_VERSION=	5.2.3
COMPONENT_PROJECT_URL=	http://tukaani.org/xz/
COMPONENT_ARCHIVE_HASH=	\
    sha256:71928b357d0a09a12a4b4c5fafca8c31c19b0e7d3b8ebb19622e96f26dbf28cb
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	5277

TPNO=			33885

SYSTEM_TEST_TARGET= configure $(SYSTEM_TEST_32_and_64)
include $(WS_MAKE_RULES)/common.mk

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
COMPONENT_SYSTEM_TEST_ENV +=	XZ_SCRIPT=$(USRBINDIR)/xz
COMPONENT_SYSTEM_TEST_ENV +=	XZDEC_SCRIPT=$(USRBINDIR)/xzdec
COMPONENT_SYSTEM_TEST_ENV +=	XZDIFF_SCRIPT=$(USRBINDIR)/xzdiff
COMPONENT_SYSTEM_TEST_ENV +=	XZGREP_SCRIPT=$(USRBINDIR)/xzgrep

include $(WS_MAKE_RULES)/shared-targets.mk

REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library/security/crypto
