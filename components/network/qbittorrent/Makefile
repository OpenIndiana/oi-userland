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
include ../../../make-rules/shared-macros.mk

COMPILER=gcc
COMPONENT_NAME=		qbittorrent
COMPONENT_VERSION=	4.4.2
COMPONENT_FMRI=		network/qbittorrent
COMPONENT_PROJECT_URL=	https://www.qbittorrent.org/
COMPONENT_SUMMARY=	Qt cross-platform application and UI framework
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:2d5bac5b837c3dfd219d8e36a777268ee7d0bfad38bc94bfd01ff07f43079bbe
COMPONENT_ARCHIVE_URL=\
	https://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_NAME)/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)/download
COMPONENT_LICENSE=	LGPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk
PATH=$(QT6_BINDIR):$(PG_BINDIR.$(BITS)):$(MYSQL_BINDIR.$(BITS)):$(GCC_ROOT)/bin:$(PATH.gnu)

GCC_VERSION = 10
OPENSSL_VERSION=1.1
CONFIGURE_ENV += Qt5Svg_LIBS="-L$(QT6_LIBDIR) -lQt6Svg"
CONFIGURE_ENV += Qt5Svg_CFLAGS="-I$(QT6_BASEDIR)/include"
LDFLAGS += -Wl,-rpath,$(QT6_LIBDIR)
CONFIGURE_OPTIONS += --prefix=$(PROTO_DIR)/usr
CONFIGURE_OPTIONS += --bindir=$(PROTO_DIR)/usr/bin
CONFIGURE_OPTIONS += --mandir=$(PROTO_DIR)/usr/share/man
CONFIGURE_OPTIONS += QT_QMAKE=$(QT6_BINDIR)
CONFIGURE_OPTIONS += PKG_CONFIG_PATH=$(OPENSSL_PKG_CONFIG_PATH):$(PKG_CONFIG_PATH.$(BITS)):$(SOURCE_DIR)/../pkgconfig

# Auto-generated dependencies
REQUIRED_PACKAGES += library/qt6
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += network/libtorrent-rasterbar
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-10-runtime
REQUIRED_PACKAGES += system/library/gcc-10-runtime
REQUIRED_PACKAGES += system/library/math
