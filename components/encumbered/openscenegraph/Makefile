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
# Copyright (c) 2022 Jake Goerzen

BUILD_STYLE=	cmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		OpenSceneGraph
COMPONENT_VERSION=	3.6.5
COMPONENT_REVISION= 2
COMPONENT_PROJECT_URL=	https://www.openscenegraph.com
COMPONENT_SUMMARY=	OpenSceneGraph - High performance 3D graphics toolkit.
COMPONENT_SRC=		OpenSceneGraph-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH=	\
	sha256:0e9e3e4cc6f463f21a901934a95e9264b231a1d5db90f72dcb4b8cc94b0d1b3b
COMPONENT_ARCHIVE_URL=  https://github.com/openscenegraph/OpenSceneGraph/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/openscenegraph
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	OSGPL
COMPONENT_LICENSE_FILE=	LICENSE.txt

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

CMAKE_CXX_FLAGS += -std=c++11

# This is to get libraries to install into /usr/lib/$(MACH64)
CMAKE_OPTIONS += -DLIB_POSTFIX=/$(MACH64)

# OpenSceneGraph doesn't yet support FFmpeg 5 or higher, we have FFmpeg 6, so disable it for now
# https://github.com/openscenegraph/OpenSceneGraph/issues/1111
CMAKE_OPTIONS += -DCMAKE_DISABLE_FIND_PACKAGE_FFmpeg=1

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += codec/jasper
REQUIRED_PACKAGES += image/library/libjpeg6
REQUIRED_PACKAGES += image/library/libjpeg6-ijg
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/giflib
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/libvncserver
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
