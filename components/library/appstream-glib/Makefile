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
# Copyright 2019 Tim Mooney.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		appstream-glib
COMPONENT_VERSION=	0.7.17
COMPONENT_FMRI=		library/$(COMPONENT_NAME)
COMPONENT_SUMMARY=	appstream-glib provides GObjects and helper methods to read and write AppStream metadata
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_PROJECT_URL=	https://people.freedesktop.org/~hughsient/appstream-glib/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
  sha256:7ca7e91d4accefa1c0d2c6e310cb3fe2686c017810e23b3f82d9f5724345e549
COMPONENT_ARCHIVE_URL= \
  https://people.freedesktop.org/~hughsient/$(COMPONENT_NAME)/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	LGPL 2+
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/meson.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

# replace the broken linker map with one that was generated on OI for
# a previous build of the library.  This file needs to be regenerated if
# new symbols are added to libappstream-glib.so
#COMPONENT_PRE_BUILD_ACTION += \
#    ( $(CP) files/appstream-glib.map $(SOURCE_DIR)/libappstream-glib/ )

#
# augment the system PKG_CONFIG_PATH with local paths in this package,
# for uuid.pc
#
CONFIGURE_ENV.32+=	PKG_CONFIG_PATH="/usr/lib/pkgconfig:$(COMPONENT_DIR)/files/lib/pkgconfig"
CONFIGURE_ENV.64+=	PKG_CONFIG_PATH="/usr/lib/amd64/pkgconfig:$(COMPONENT_DIR)/files/lib/$(MACH64)/pkgconfig"

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	-Drpm=false
CONFIGURE_OPTIONS+=	-Dalpm=false
CONFIGURE_OPTIONS+=	-Dgtk-doc=true
CONFIGURE_OPTIONS+=	-Dintrospection=true
CONFIGURE_OPTIONS+=	-Dstemmer=false

# Tell g-ir-scanner about compiler
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libyaml
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
