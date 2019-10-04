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

COMPONENT_NAME=		libmediaart
COMPONENT_VERSION=	1.9.4
COMPONENT_FMRI=		library/$(COMPONENT_NAME)
COMPONENT_SUMMARY=	libmediaart - a library for managing, extracting and handling media art caches
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_PROJECT_URL=	https://github.com/GNOME/libmediaart
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
  sha256:a57be017257e4815389afe4f58fdacb6a50e74fd185452b23a652ee56b04813d
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/1.9/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	LGPL 2.1
COMPONENT_LICENSE_FILE=	COPYING.LESSER

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION += ( $(CLONEY) $(SOURCE_DIR) $(@D) )

PATH=$(PATH.gnu)

CONFIGURE_SCRIPT=	$(@D)/configure

# always use the GdkPixbuf implementation
CONFIGURE_OPTIONS+=	--enable-gdkpixbuf=yes

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+=	--enable-gtk-doc

# Tell g-ir-scanner about compiler
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
