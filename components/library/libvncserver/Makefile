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
# Copyright 2018 Harry Liebel
# Copyright 2023 Andreas Wacknitz
#

BUILD_BITS= 64
BUILD_STYLE= cmake
OPENSSL_VERSION= 3.1
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libvncserver
COMPONENT_VERSION=	0.9.14
COMPONENT_SUMMARY=	VNC server and client C libraries
COMPONENT_DESCRIPTION=	LibVNCServer/LibVNCClient are cross-platform C libraries that allow you to easily implement VNC server or client functionality in your program.
COMPONENT_PROJECT_URL=	https://libvnc.github.io
COMPONENT_SRC=		$(COMPONENT_NAME)-LibVNCServer-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	LibVNCServer-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:83104e4f7e28b02f8bf6b010d69b626fae591f887e949816305daebae527c9a5
COMPONENT_ARCHIVE_URL=	https://github.com/LibVNC/$(COMPONENT_NAME)/archive/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/libvncserver
COMPONENT_CLASSIFICATION= Development/C
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -lsocket -lnsl

CFLAGS  += -I$(OPENSSL_INCDIR)
LDFLAGS += -L$(OPENSSL_LIBDIR)

# build with the system default libjpeg
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
CPPFLAGS += $(JPEG_CPPFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

# Needed to find the correct jpeg libs
CMAKE_OPTIONS += -DJPEG_INCLUDE_DIR=$(JPEG_INCDIR)
CMAKE_OPTIONS += -DJPEG_LIBRARY=$(JPEG_LIBDIR)/libjpeg.so
# We prefer openssl over gnutls
CMAKE_OPTIONS += -DWITH_GNUTLS=OFF

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/lzo
REQUIRED_PACKAGES += library/security/openssl-31
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
