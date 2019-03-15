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
# Copyright 2017 Aurelien Larcher
# Copyright 2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libunistring
COMPONENT_VERSION=	0.9.10
COMPONENT_FMRI=		library/libunistring
COMPONENT_SUMMARY=	libunistring - library for manipulating Unicode strings
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/libunistring/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL= \
	http://ftp.gnu.org/gnu/libunistring/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
	sha256:eb8fb2c3e4b6e2d336608377050892b54c3c983b646c561836550863003c05d7
COMPONENT_LICENSE=     GPLv3, LGPLv3

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS += --disable-static

# Test failure
unexport SHELLOPTS

COMPONENT_TEST_MASTER = \
	$(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
 	'-n ' \
	'-e "/TOTAL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/ERROR/p" '

build:    $(BUILD_32_and_64)

install:  $(INSTALL_32_and_64)

# Known failure: test-localename
test:    $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
