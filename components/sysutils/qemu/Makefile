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
# Copyright 2023 OmniOS Community Edition (OmniOSce) Association.
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

PATH= $(PATH.gnu)

COMPONENT_NAME=		qemu
COMPONENT_VERSION=	7.2.0
COMPONENT_SUMMARY=	\
		A generic and open source machine emulator and virtualizer
COMPONENT_PROJECT_URL=	https://www.qemu.org/
COMPONENT_FMRI=		system/qemu
COMPONENT_CLASSIFICATION= System/Virtualization
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:5b49ce2687744dad494ae90a898c52204a3406e84d072482a1e1be854eeb2157
COMPONENT_ARCHIVE_URL=	https://download.qemu.org/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).sig
COMPONENT_LICENSE= 	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk
include $(WS_MAKE_RULES)/ninja.mk

COMPONENT_POST_INSTALL_ACTION = \
( find $(PROTOUSRBINDIR) -name 'qemu-system-*' -type f -exec strip {} + )
COMPONENT_INSTALL_ARGS=

CPPFLAGS	+= $(JPEG_CPPFLAGS)
CFLAGS		+= $(JPEG_CFLAGS)
LDFLAGS		+= $(JPEG_LDFLAGS)
LDFLAGS		+= -lumem

# Build dependencies
REQUIRED_PACKAGES += library/libtasn1

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/vte-291
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += library/lzo
REQUIRED_PACKAGES += library/sdl2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libepoxy
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/mesa
