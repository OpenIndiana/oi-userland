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
# Copyright 2022 Niklas Poslovski
#

USE_DEFAULT_TEST_TRANSFORMS=yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libgdiplus
COMPONENT_VERSION=      6.1
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      Open Source Implementation of the GDI+ API
COMPONENT_PROJECT_URL=  https://www.mono-project.com/docs/gui/libgdiplus/
COMPONENT_FMRI=         library/desktop/libgdiplus
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:97d5a83d6d6d8f96c27fb7626f4ae11d3b38bc88a1726b4466aeb91451f3255b
COMPONENT_ARCHIVE_URL=	https://download.mono-project.com/sources/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=      MIT

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)
unexport SHELLOPTS

# build with the distribution preferred libjpeg implementation
CFLAGS            +=    $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS          +=    $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS           +=    $(JPEG_LDFLAGS)

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/giflib
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
