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
# Copyright 2020 Alexander Pyhalov
# Copyright 2019 Tim Mooney
#

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gegl
COMPONENT_MJR_VERSION= 0.4
COMPONENT_VERSION= $(COMPONENT_MJR_VERSION).48
COMPONENT_SUMMARY= GEGL (Generic Graphics Library) is a graph based image processing framework
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:418c26d94be8805d7d98f6de0c6825ca26bd74fcacb6c188da47533d9ee28247
COMPONENT_ARCHIVE_URL= https://download.gimp.org/pub/gegl/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://www.gegl.org/
COMPONENT_FMRI=	image/library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE= GPLv3, LGPLv3

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# strptime needs this:
CFLAGS += -D_XOPEN_SOURCE_EXTENDED=1
CFLAGS += $(CFLAGS.$(BITS))

# build with the distribution default libjpeg
CFLAGS		+=    $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS	+=    $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS		+=    $(JPEG_LDFLAGS)

CONFIGURE_OPTIONS+= --datadir=$(USRSHAREDIR)
CONFIGURE_OPTIONS+= -Ddocs=false
CONFIGURE_OPTIONS+= -Dgi-docgen=disabled
CONFIGURE_OPTIONS+= -Dvapigen=disabled
CONFIGURE_OPTIONS+= -Dworkshop=true
# libav is from encumbered
CONFIGURE_OPTIONS+= -Dlibav=disabled

# gobject-introspection requires this
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_TEST_ENV += LD_LIBRARY_PATH=$(BUILD_DIR_64)/gegl
COMPONENT_TEST_TRANSFORMS += \
	' -e "s/[0-9]*\.[0-9]*s//" ' \
	' -e "/OK/p" ' \
	' -e "/SKIP/p" ' \
	' -e "/FAIL/p" ' \
	' -e "/Summary/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += codec/jasper
REQUIRED_PACKAGES += image/library/babl
REQUIRED_PACKAGES += image/library/lensfun
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libraw
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/openexr
REQUIRED_PACKAGES += library/sdl2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
