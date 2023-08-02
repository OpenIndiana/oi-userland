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
# Copyright 2022 Daniel Chan
#

BUILD_BITS=		64
BUILD_STYLE=	cmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		quazip
HUMAN_VERSION=		1.3
COMPONENT_VERSION=	1.3.0
COMPONENT_REVISION= 1
COMPONENT_FMRI=		library/quazip
COMPONENT_PROJECT_URL=	https://github.com/stachenov/$(COMPONENT_NAME)
COMPONENT_SUMMARY=	C++ wrapper for Gilles Vollant's ZIP/UNZIP package using Trolltech's Qt library
COMPONENT_SRC=			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:c1239559cd6860cab80a0fd81f4204e606f9324f702dab6166b0960676ee1754
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)
PATH=$(PATH.gnu)
include $(WS_MAKE_RULES)/common.mk
LDFLAGS += -Wl,-rpath,$(QT5_LIBDIR)
CMAKE_ENV += CMAKE_PREFIX_PATH="$(QT5_LIBDIR)/cmake:$(USRLIBDIR.$(BITS))/cmake/"

# Build dependencies
REQUIRED_PACKAGES += library/qt5
# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
