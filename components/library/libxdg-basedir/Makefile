#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2017 Dariusz Sendkowski
#
BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libxdg-basedir
COMPONENT_VERSION=      1.2.3
COMPONENT_PROJECT_URL=  https://github.com/devnev/$(COMPONENT_NAME)
COMPONENT_SUMMARY=      An implementation of the XDG Base Directory specifications.
COMPONENT_FMRI=         library/xdg/libxdg-basedir 
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:ff30c60161f7043df4dcc6e7cdea8e064e382aa06c73dcc3d1885c7d2c77451d
COMPONENT_ARCHIVE_URL=  https://github.com/devnev/$(COMPONENT_NAME)/archive/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= COPYING

#TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -f -i)

# Tests will fail without unexport SHELLOPTS
unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS += \
    '-n ' \
	'-e "/PASS:/p" ' \
	'-e "/FAIL:/p" ' \
	'-e "/SKIP:/p" ' \
	'-e "/ERROR:/p" ' \
	'-e "/TOTAL:/p" ' \
	'-e "/====/p" ' \
	'-e "/^Testsuite/p" ' \
	'-e "/^See /p" ' \
	'-e "/^Please /p" '

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
