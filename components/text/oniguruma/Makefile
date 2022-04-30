#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2021 Till Wegmueller
#

BUILD_BITS=64 # for binaries or 32_and_64 for libraries
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			oniguruma
COMPONENT_VERSION_BASE=		6.9.8
COMPONENT_VERSION=		$(COMPONENT_VERSION_BASE)
COMPONENT_SUMMARY=		oniguruma - regular expression library 
COMPONENT_PROJECT_URL=		https://github.com/kkos/oniguruma
COMPONENT_FMRI=			text/oniguruma
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SRC=			onig-$(COMPONENT_VERSION_BASE)
COMPONENT_SRC2=			onig-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC2).tar.gz
COMPONENT_ARCHIVE_URL=		https://github.com/kkos/$(COMPONENT_NAME)/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=		sha256:28cd62c1464623c7910565fb1ccaaa0104b2fe8b12bcd646e81f73b47535213e
COMPONENT_LICENSE=		BSD like
COMPONENT_LICENSE_FILE=		COPYING

#TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --enable-static=no

unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/=====/p" ' \
	'-e "/Testsuite summary/p" ' \
	'-e "/TOTAL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/ERROR/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
