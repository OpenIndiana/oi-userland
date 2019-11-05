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
# Copyright 2016-2017 Aurelien Larcher.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gst-plugins-bad1
COMPONENT_VERSION= 1.12.5
COMPONENT_SUMMARY= GNOME streaming media framework plugins
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_FMRI= library/audio/gstreamer1/plugin/bad
COMPONENT_SRC_NAME= gst-plugins-bad
COMPONENT_SRC= $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:40f82fa775ce8ecfc930fd13073e8643b90cba9b6f8dd2462ec45a93120c7d81
COMPONENT_ARCHIVE_URL= \
  http://gstreamer.freedesktop.org/src/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://gstreamer.freedesktop.org/
COMPONENT_LICENSE= LGPLv2

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = ( cd $(SOURCE_DIR) && aclocal -I ./m4 -I./common/m4 &&\
                          autoheader &&\
                          automake -a -f -c --gnu &&\
                          autoconf )
gcc_OPT = -O2

PATH = $(PATH.gnu)

CFLAGS += -I/usr/X11/include/mesa
CFLAGS += -I/usr/X11/include

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/$(MACH64)
CONFIGURE_OPTIONS += --disable-examples
CONFIGURE_OPTIONS += --enable-external
CONFIGURE_OPTIONS += --enable-opengl
CONFIGURE_OPTIONS += --disable-gles2
CONFIGURE_OPTIONS += --disable-egl
CONFIGURE_OPTIONS += --with-default-audiosrc=autoaudiosrc
CONFIGURE_OPTIONS += --with-default-audiosink=autoaudiosink
CONFIGURE_OPTIONS += --with-default-videosink=autovideosink
CONFIGURE_OPTIONS += --enable-openexr

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CXXFLAGS="$(CXXFLAGS)"
COMPONENT_INSTALL_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ENV += CXXFLAGS="$(CXXFLAGS)"

COMPONENT_INSTALL_ENV += GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Build dependencies
REQUIRED_PACKAGES += system/header/header-drm

# Auto-generated dependencies
REQUIRED_PACKAGES += audio/faac
REQUIRED_PACKAGES += audio/faad2
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += image/library/openjpeg
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/audio/libdca
REQUIRED_PACKAGES += library/audio/libgsm
REQUIRED_PACKAGES += library/audio/libmpcdec
REQUIRED_PACKAGES += library/audio/openal
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/libvdpau
REQUIRED_PACKAGES += library/ilmbase
REQUIRED_PACKAGES += library/libofa
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/neon
REQUIRED_PACKAGES += library/nettle
REQUIRED_PACKAGES += library/openexr
REQUIRED_PACKAGES += library/opus
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/video/libass
REQUIRED_PACKAGES += library/video/libdvdnav
REQUIRED_PACKAGES += library/video/libdvdread
REQUIRED_PACKAGES += library/video/libmms
REQUIRED_PACKAGES += library/video/libschroedinger
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/orc
REQUIRED_PACKAGES += video/rtmpdump
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libdrm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
