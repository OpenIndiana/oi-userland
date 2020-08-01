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
# Copyright (c) 2015 Alexander Pyhalov
#

BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		geeqie
COMPONENT_VERSION=	1.5.1
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.geeqie.org/
COMPONENT_SUMMARY=	Geeqie is a lightweight Gtk+ based image viewer
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:4854d5d323c31f8f4068fd73ab2c454ff91e826c4ca4d37b22c246ad14dea10a
COMPONENT_ARCHIVE_URL=	 http://www.geeqie.org/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Applications/Graphics and Imaging
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_FMRI=         image/viewer/geeqie

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && NOCONFIGURE=1 ./autogen.sh )

PATH=$(PATH.gnu)

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

CONFIGURE_ENV += LIBS="-lm -lsocket -lnsl"

CFLAGS+= $(CPP_XPG6MODE)

CONFIGURE_OPTIONS += --disable-gtk3

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += image/library/exiv2
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += runtime/lua-53
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
# Required by libssp
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
