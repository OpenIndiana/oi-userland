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
# Copyright 2016 Jim Klimov
# Copyright 2022 Friedrich Kink
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         cxxtools
COMPONENT_VERSION=      3.0
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=      Cxxtools is a comprehensive C++ class library for Unix and Linux
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:07b18037fb0983f6292f5c8d53e2369e9e7a9711df2c9ad50838aacbc8c62f7c
COMPONENT_ARCHIVE_URL=	http://www.tntnet.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.tntnet.org/cxxtools.html
COMPONENT_FMRI=         library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CXXFLAGS += -std=c++11

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --with-ssl=yes
CONFIGURE_OPTIONS += LDFLAGS=-L$(OPENSSL_LIBDIR)
CONFIGURE_OPTIONS += CPPFLAGS=-I$(OPENSSL_INCDIR)
CONFIGURE_OPTIONS += PKG_CONFIG_PATH=$(OPENSSL_PKG_CONFIG_PATH)


# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
