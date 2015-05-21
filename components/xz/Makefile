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
# Copyright (c) 2012, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		xz
COMPONENT_VERSION=	5.2.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://tukaani.org/xz/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:b918b6648076e74f8d7ae19db5ee663df800049e187259faf5eb997a7b974681
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/xz

TPNO=			21937

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

ASLR_MODE = $(ASLR_ENABLE)

# common targets
configure:	$(CONFIGURE_32_and_64)

build:		$(BUILD_32_and_64)

include $(WS_MAKE_RULES)/shared-targets.mk

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/crypto
