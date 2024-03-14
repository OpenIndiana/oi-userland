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
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE= cmake
OPENSSL_VERSION= 3.1
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		qbittorrent
COMPONENT_VERSION=	4.5.5
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Qt cross-platform application and UI framework
COMPONENT_PROJECT_URL=	https://www.qbittorrent.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:8e84a5ba63c7203cfb2e5bb23e27d000120fb8e9dfb6e9f9a1064dce1b9294e9
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_NAME)/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)/download
COMPONENT_FMRI=			network/qbittorrent
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_LICENSE=		LGPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(QT6_BINDIR):$(PG_BINDIR.$(BITS)):$(MYSQL_BINDIR.$(BITS)):$(GCC_ROOT)/bin:$(PATH.gnu)

LDFLAGS += -Wl,-rpath,$(QT6_LIBDIR)
CMAKE_OPTIONS += -DQT6=On
CMAKE_OPTIONS += -DTESTING=On
CMAKE_OPTIONS += -DCMAKE_PREFIX_PATH=$(QT6_LIBDIR)/cmake

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/qt6
REQUIRED_PACKAGES += library/security/openssl-31
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += network/libtorrent-rasterbar
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
