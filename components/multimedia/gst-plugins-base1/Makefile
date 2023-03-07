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

BUILD_BITS= 32_and_64
BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gst-plugins-base1
COMPONENT_VERSION=      1.22.1
#COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      GNOME streaming media framework plugins
COMPONENT_SRC_NAME= 	gst-plugins-base
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:59bcaeacc5646b8dbdcfa4ef20ca6e818dd234910efb4cee1bbea441a3801c69
COMPONENT_PROJECT_URL=  https://gstreamer.freedesktop.org/
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/src/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/audio/gstreamer1/plugin/base
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_LICENSE=      GPLv2,LGPLv2

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CFLAGS += -I/usr/X11/include -lsocket
# build with the distribution preferred libjpeg implementation
CFLAGS             +=           $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS           +=           $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS            +=           $(JPEG_LDFLAGS)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/$(MACH64)
CONFIGURE_OPTIONS += -Dalsa=disabled
CONFIGURE_OPTIONS += -Dorc=enabled
CONFIGURE_OPTIONS += -Dpango=enabled
#CONFIGURE_OPTIONS += --disable-gles2
#CONFIGURE_OPTIONS += -Dgl=disabled
CONFIGURE_OPTIONS += -Dgl_api=opengl
CONFIGURE_OPTIONS += -Dgl_platform=glx,egl
CONFIGURE_OPTIONS += -Dgl_winsys=x11,egl
CONFIGURE_OPTIONS += -Dgl-graphene=disabled
#CONFIGURE_OPTIONS += --enable-external
#CONFIGURE_OPTIONS += --enable-experimental
CONFIGURE_OPTIONS.32 += -Dintrospection=disabled
CONFIGURE_OPTIONS.64 += -Dintrospection=enabled
#CONFIGURE_OPTIONS += --with-default-audiosrc=autoaudiosrc
#CONFIGURE_OPTIONS += --with-default-audiosink=autoaudiosink
#CONFIGURE_OPTIONS += --with-default-videosink=autovideosink
CONFIGURE_OPTIONS += -Dpackage-origin="https://github.com/OpenIndiana/oi-userland"

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_INSTALL_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ENV += CC="$(CC)"

unexport SHELLOPTS
# (first) delete the timing information from any line
# delete the "exit status N", it can cause issues too
# print lines that start with " N/NNN"
# print everything between "^Ok:" and "^Timeout:"
# delete the ninja log-related stuff at the end
# elements_compositor and elements_libvisual can non-determinstically
# fail, so leave them and the totals out
# many of the GL tests require a DISPLAY, so filter out libs_gstgl*,
# elements_gl*, and pipelines_gl*
COMPONENT_TEST_TRANSFORMS += \
    '-n ' \
    '-e "/elements_compositor/d" ' \
    '-e "/elements_libvisual/d" ' \
    '-e "/libs_gstgl/d" ' \
    '-e "/elements_gl/d" ' \
    '-e "/pipelines_gl/d" ' \
    '-e "s/[ 	]*[0-9][0-9]*\.[0-9][0-9]s//" ' \
    '-e "s/[ 	]*exit status [0-9][0-9]*//" ' \
    '-e "/^[ 	]*[0-9][0-9]*\/[0-9][0-9]* /p" ' \
    '-e "/^Summary of/p" ' \
    '-e "/^Ok:/,/^Timeout:/d" ' \
    '-e "/^Full log written.*/,/^ninja: build stopped.*/d" '

# Build dependencies
REQUIRED_PACKAGES += x11/library/mesa

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += codec/libtheora
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/libvisual
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += library/opus
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/orc
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxv
