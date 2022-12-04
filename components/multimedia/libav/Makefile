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
# Copyright 2022 Friedrich Kink
#

OPENSSL_VERSION= 3.1

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libav
COMPONENT_VERSION=	12.3
COMPONENT_FMRI=		multimedia/libav
COMPONENT_SUMMARY=	A set of portable, functional and high-performance libraries for \
	dealing with multimedia formats of all sorts
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:115b659022dd387f662e26fbc5bc0cc14ec18daa100003ffd34f4da0479b272e
COMPONENT_PROJECT_URL=	https://libav.org
COMPONENT_ARCHIVE_URL=	https://libav.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	LGPLv2.1,MIT,X11,BSD
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET=$(NO_TESTS) 

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS=

CONFIGURE_OPTIONS  += --prefix=/usr
CONFIGURE_OPTIONS  += --libdir=$(USRLIBDIR64)
CONFIGURE_OPTIONS  += --shlibdir=$(USRLIBDIR64)
CONFIGURE_OPTIONS  += --disable-static
CONFIGURE_OPTIONS  += --enable-shared
#openssl is nonfree and --enable-nonfree is not specified
#CONFIGURE_OPTIONS  += --enable-openssl
CONFIGURE_OPTIONS  += --enable-runtime-cpudetect

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/graphics/libvdpau
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
