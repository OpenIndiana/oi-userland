#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Alexander Pyhalov
# Copyright 2019 Michal Nowak
#

BUILD_BITS=		32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libidn2
COMPONENT_VERSION=	2.3.0
COMPONENT_SUMMARY=	An implementation of IDNA2008 internationalized domain names
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:e1cb1db3d2e249a6a3eb6f0946777c2e892d5c5dc7bd91c74394fc3a01cab8b5
COMPONENT_ARCHIVE_URL= \
	http://ftp.gnu.org/gnu/libidn/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/libidn/
COMPONENT_FMRI=		library/libidn2
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	LGPLv3, GPLv2

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-static=no
CONFIGURE_OPTIONS += --includedir=/usr/include/idn2

COMPONENT_TEST_TRANSFORMS += '-ne "/^SKIP/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^PASS/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^FAIL/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^TOTAL/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^===/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^\# /p" '

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libunistring
REQUIRED_PACKAGES += system/library
