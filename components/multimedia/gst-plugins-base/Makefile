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
# Copyright 2016-2018 Aurelien Larcher.  All rights reserved.
# Copyright 2019 Michal Nowak
# Copyright 2022-2023 Niklas Poslovski
#

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gst-plugins-base
COMPONENT_VERSION=	1.24.12
COMPONENT_SUMMARY=      GNOME streaming media framework plugins
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:f6efbaa8fea8d00bc380bccca76a530527b1f083e8523eafb3e9b1e18bc653d3
COMPONENT_PROJECT_URL=  https://gstreamer.freedesktop.org/
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/audio/gstreamer/plugin/base
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_LICENSE=	LGPL-2.1-only
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += -Dalsa=disabled
CONFIGURE_OPTIONS += -Dorc=enabled
CONFIGURE_OPTIONS += -Dpango=enabled
CONFIGURE_OPTIONS += -Dgl_api=opengl
CONFIGURE_OPTIONS += -Dgl_platform=glx,egl
CONFIGURE_OPTIONS += -Dgl_winsys=x11,egl
CONFIGURE_OPTIONS += -Dgl-graphene=disabled
CONFIGURE_OPTIONS += -Dintrospection=enabled
# wglext is needed for Windows only
CONFIGURE_OPTIONS += -Dgl-headers:wglext=disabled
CONFIGURE_OPTIONS += -Dpackage-origin="https://github.com/OpenIndiana/oi-userland"

# Dynamic library version number
SOVER := 0.$(shell printf '%02s%02s' $(wordlist 2,3,$(subst ., ,$(COMPONENT_VERSION)))).0
SOVER_RE = $(subst .,\.,$(SOVER))

# This is a workaround for the following meson bug:
# https://github.com/mesonbuild/meson/issues/6541#issuecomment-2122142024
COMPONENT_POST_INSTALL_ACTION += \
	$(ELFEDIT) -e 'dyn:runpath /usr/lib/xorg/amd64:$(GCC_LIBDIR)' \
	$(PROTOUSRLIBDIR.$(BITS))/libgstallocators-1.0.so.$(SOVER) ;

# Replace library version number by SOVER
GENERATE_EXTRA_CMD += | $(GSED) -e 's/$(SOVER_RE)/$$(SOVER)/'

# SOVER is needed for manifest processing
PKG_MACROS += SOVER=$(SOVER)

# Build dependencies
REQUIRED_PACKAGES += x11/library/mesa

# gst-devtools is optional testing dependency.  However, if it is available it
# must be at the same major version as the main gstreamer package to run tests
# successfully.
GST_DEVTOOLS_VERSION = \
	$(shell $(GMAKE) -f $(WS_COMPONENTS)/encumbered/gst-devtools1/Makefile print-value-COMPONENT_VERSION)
ifeq ($(basename $(GST_DEVTOOLS_VERSION)),$(basename $(COMPONENT_VERSION)))
TEST_REQUIRED_PACKAGES += library/audio/gstreamer1/devtools
else
TEST_CONFLICTING_PACKAGES += library/audio/gstreamer1/devtools
endif

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += codec/libtheora
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/libvisual
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += library/opus
REQUIRED_PACKAGES += library/orc
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libdrm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxv
