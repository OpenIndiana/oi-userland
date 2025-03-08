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

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		quazip
HUMAN_VERSION=		1.5
COMPONENT_VERSION=	1.5.0
COMPONENT_SUMMARY=	C++ wrapper for Gilles Vollant's ZIP/UNZIP package using Trolltech's Qt library
COMPONENT_PROJECT_URL=	https://github.com/stachenov/$(COMPONENT_NAME)
COMPONENT_SRC=			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:405b72b6e76c8987ff41a762523b8f64876ba406d8a831d268ee0b63f1369582
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_FMRI=		library/quazip
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

LDFLAGS += -Wl,-rpath,$(QT5_LIBDIR)
CMAKE_ENV += CMAKE_PREFIX_PATH="$(QT5_LIBDIR)/cmake:$(USRLIBDIR.$(BITS))/cmake/"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
