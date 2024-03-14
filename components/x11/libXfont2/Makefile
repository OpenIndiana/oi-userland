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
# Copyright 2017 Aurelien Larcher
#

X11_CATEGORY=LIB
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= libXfont2
COMPONENT_VERSION= 2.0.6
COMPONENT_REVISION= 1
COMPONENT_FMRI= x11/library/libxfont2
COMPONENT_SUMMARY= libXfont2 - library for X servers and utilities to access font files
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:74ca20017eb0fb3f56d8d5e60685f560fc85e5ff3d84c61c4cb891e40c27aef4
COMPONENT_LICENSE_FILE= COPYING

DROP_STATIC_LIBRARIES = yes

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = (cd $(@D) && PATH="$(PATH)" autoreconf -f -i)

CONFIGURE_LIBDIR.32 = /usr/lib/xorg
CONFIGURE_LIBDIR.64 = /usr/lib/xorg/$(MACH64)

CONFIGURE_OPTIONS += --enable-freetype
CONFIGURE_OPTIONS += --enable-fc
CONFIGURE_OPTIONS += --enable-builtins
CONFIGURE_OPTIONS += --with-bzip2
CONFIGURE_OPTIONS += --with-pkgconfigdir=$(PKG_CONFIG_PATH.$(BITS))

CONFIGURE_ENV += LIB_MAN_SUFFIX=3xfont2

# Build dependencies
REQUIRED_PACKAGES += x11/library/xtrans

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libfontenc
