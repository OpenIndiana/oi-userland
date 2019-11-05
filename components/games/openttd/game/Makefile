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
# Copyright 2016 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
# Copyright 2016 Jim Klimov <jimklimov@gmail.com>
# Copyright 2018 Harry Liebel <hliebel@gmail.com>
#

PREFERRED_BITS=		64

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openttd
COMPONENT_VERSION=	1.8.0
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.openttd.org/en/
COMPONENT_FMRI=		games/openttd/openttd-core
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-source.tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:c2d32d9d736d27202a020027a3729ae763f5432ae6f424891e57a4095eeb087f
COMPONENT_ARCHIVE_URL=	https://binaries.openttd.org/releases/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	OpenTTD is an open source simulation game based upon Transport Tycoon Deluxe
COMPONENT_CLASSIFICATION="Applications/Games"

CONFIGURE_DEFAULT_DIRS=no

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS += --prefix-dir=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --binary-dir=bin
CONFIGURE_OPTIONS += --data-dir=share/openttd
CONFIGURE_OPTIONS += --install-dir=$(PROTO_DIR)
CONFIGURE_OPTIONS += --disable-strip
CONFIGURE_OPTIONS += --without-allegro
CONFIGURE_OPTIONS += --with-sdl
CONFIGURE_OPTIONS += --with-zlib
CONFIGURE_OPTIONS += --with-liblzma
CONFIGURE_OPTIONS += --with-liblzo2
CONFIGURE_OPTIONS += --with-png
CONFIGURE_OPTIONS += --with-freetype
CONFIGURE_OPTIONS += --with-fontconfig
CONFIGURE_OPTIONS += --without-icu
CONFIGURE_OPTIONS += --without-iconv
CONFIGURE_OPTIONS += --without-menu-entry

COMPONENT_BUILD_ARGS += DO_NOT_INSTALL_CHANGE_LOG=1
COMPONENT_BUILD_ARGS += DO_NOT_INSTALL_LICENSE=1

COMPONENT_PRE_CONFIGURE_ACTION=$(CLONEY) $(SOURCE_DIR) $(@D)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/lzo
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += library/xdg/libxdg-basedir
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
