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
# Copyright 2025 Klaus Ziegler
#

BUILD_STYLE= cmake
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libvncserver
COMPONENT_VERSION=	0.9.15
COMPONENT_SUMMARY=	VNC server and client C libraries
COMPONENT_DESCRIPTION=	LibVNCServer/LibVNCClient are cross-platform C libraries that allow you to easily implement VNC server or client functionality in your program.
COMPONENT_PROJECT_URL=	https://libvnc.github.io
COMPONENT_SRC=		$(COMPONENT_NAME)-LibVNCServer-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	LibVNCServer-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:62352c7795e231dfce044beb96156065a05a05c974e5de9e023d688d8ff675d7
COMPONENT_ARCHIVE_URL=	https://github.com/LibVNC/$(COMPONENT_NAME)/archive/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/libvncserver
COMPONENT_CLASSIFICATION= Development/C
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -lsocket -lnsl

# make gcc-14 happy
CFLAGS   += -Wno-implicit-function-declaration
# We prefer openssl over gnutls
CMAKE_OPTIONS += -DWITH_GNUTLS=OFF
# newer cmake needs this
CMAKE_OPTIONS += -DCMAKE_POLICY_VERSION_MINIMUM=3.5

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/lzo
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
