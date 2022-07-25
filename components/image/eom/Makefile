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
# Copyright 2017 Alexander Pyhalov
# Copyright 2019 Michal Nowak
# Copyright (c) 2021 Tim Mooney.  All rights reserved
# Copyright 2022 Andreas Wacknitz
#

MATE_CATEGORY= APP
BUILD_STYLE= configure
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/mate.mk

COMPONENT_NAME=		eom
COMPONENT_MJR_VERSION=	1.26
COMPONENT_MNR_VERSION=	0
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      MATE image viewer
COMPONENT_ARCHIVE_HASH= sha256:27f169aa396ddbc75740bf802bef1c0251771ca0747b5a727ff985c03dc067db
COMPONENT_ARCHIVE_URL=  https://pub.mate-desktop.org/releases/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION= Applications/Graphics and Imaging
COMPONENT_FMRI=		image/viewer/eom

include $(WS_MAKE_RULES)/common.mk

# build with the system default libjpeg
CFLAGS		+=    $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS	+=    $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
CPPFLAGS	+=    $(JPEG_CPPFLAGS)
LDFLAGS		+=    $(JPEG_LDFLAGS)

CFLAGS += -std=c99 -D_XOPEN_SOURCE=600 -D__EXTENSIONS__

CONFIGURE_ENV+=	CPPFLAGS="$(CPPFLAGS)"

COMPONENT_INSTALL_ENV+=	GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# formerly part of auto-generated dependencies, no longer detected
REQUIRED_PACKAGES += system/library/libdbus-glib

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libpeas
REQUIRED_PACKAGES += library/desktop/mate/mate-desktop
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
