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
# Copyright (c) 2018, Michal Nowak
# Copyright (c) 2021, Nona Hansel
#

BUILD_BITS=	64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		diffutils
COMPONENT_VERSION=	3.10
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	GNU Diffutils is a package of several programs related to finding differences between files
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/diffutils/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:90e5e93cc724e4ebe12ede80df1634063c7a855692685919bfe60b556c9bd09e
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/diffutils/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		text/gnu-diffutils
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv3, FDLv1.3

include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

CFLAGS += $(CPP_LARGEFILES)
CPPFLAGS += $(CPP_LARGEFILES)

CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_PREFIX)/gnu/bin
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)

# Tests failure
unexport SHELLOPTS

COMPONENT_TEST_DIR = $(@D)/tests

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^make.*: Leaving directory.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Nothing to be.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^/usr/gnu/bin/make.*$$|XXX_CC_XXX|g" ' \
	'-e "/^XXX_CC_XXX$$/d" '

COMPONENT_SYSTEM_TEST_DIR = $(@D)/tests
# Note on tests: Some tests require the new version already to be installed because we have paths (eg. for diff3) hardcoded.
# Even setting the PATH for the tests might not work as intended:
COMPONENT_SYSTEM_TEST_ENV += PATH="$(PROTO_DIR)/usr/gnu/bin:$(PATH)"

ASLR_MODE = $(ASLR_ENABLE)

# Build dependencies
REQUIRED_PACKAGES += text/gnu-gettext

# Test dependency
TEST_REQUIRED_PACKAGES += developer/debug/valgrind

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
