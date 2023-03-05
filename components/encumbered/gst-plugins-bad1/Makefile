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
# Copyright 2019 Michal Nowak
# Copyright 2021 Tim Mooney.  All rights reserved.
# Copyright 2022-2023 Niklas Poslovski
#

BUILD_BITS= 64
BUILD_STYLE=	meson
USE_OPENSSL11=	yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gst-plugins-bad1
COMPONENT_VERSION=      1.22.1
#COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      GNOME streaming media framework plugins
COMPONENT_SRC_NAME=	gst-plugins-bad
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:2f39b6f222d98666f9ff420a00233e336949953a846237c2bfafc8805f509f0e
COMPONENT_PROJECT_URL=  https://gstreamer.freedesktop.org
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/src/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/audio/gstreamer1/plugin/bad
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_LICENSE=      LGPLv2

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

# In the past optimisation has been reduced for unknown readons. The actual test results don't seem to be different nowadays:
#gcc_OPT = -O2

PATH = $(PATH.gnu)

CFLAGS += -I/usr/X11/include/mesa
CFLAGS += -I/usr/X11/include

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += -Dexamples=disabled
CONFIGURE_OPTIONS += -Dopenexr=enabled
CONFIGURE_OPTIONS += -Dintrospection=enabled
CONFIGURE_OPTIONS += -Dgpl=enabled
CONFIGURE_OPTIONS += -Dspandsp=disabled
# if someone can weigh in on the fdk-aac license, adding fdk-aac might be
# be nice.
# Openh264 has no licensing issues but needs some porting
CONFIGURE_OPTIONS += -Dpackage-origin="https://github.com/OpenIndiana/oi-userland"

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CXX="$(CXX)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CXXFLAGS="$(CXXFLAGS)"
COMPONENT_INSTALL_ENV += CC="$(CC)"
COMPONENT_INSTALL_ENV += CXX="$(CXX)"
COMPONENT_INSTALL_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ENV += CXXFLAGS="$(CXXFLAGS)"

COMPONENT_INSTALL_ENV += GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

unexport SHELLOPTS
# (first) delete the timing information from any line
# delete the "exit status N", it can cause issues too
# print lines that start with " N/NNN"
# print everything between "^Ok:" and "^Timeout:"
# delete the ninja log-related stuff at the end
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "s/[ 	]*[0-9][0-9]*\.[0-9][0-9]s//" ' \
	'-e "s/[ 	]*exit status [0-9][0-9]*//" ' \
	'-e "/^[ 	]*[0-9][0-9]*\/[0-9][0-9]* /p" ' \
	'-e "/^Summary of/p" ' \
	'-e "/^Ok:/,/^Timeout:/p" ' \
	'-e "/^Full log written.*/,/^ninja: build stopped.*/d" '


# Build dependencies
# gstkcms now required libdrm >= 2.4.98, so not currently being built
REQUIRED_PACKAGES += system/header/header-drm
# Introspection
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += audio/faac
REQUIRED_PACKAGES += audio/faad2
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += image/library/openjpeg
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/audio/libdca
REQUIRED_PACKAGES += library/audio/libgsm
REQUIRED_PACKAGES += library/audio/openal
REQUIRED_PACKAGES += library/audio/soundtouch
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/imath
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/libqrencode
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/neon
REQUIRED_PACKAGES += library/nettle
REQUIRED_PACKAGES += library/openexr
REQUIRED_PACKAGES += library/opus
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/video/libass
REQUIRED_PACKAGES += library/video/libdvdnav
REQUIRED_PACKAGES += library/video/libdvdread
REQUIRED_PACKAGES += library/video/x265
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/orc
REQUIRED_PACKAGES += video/rtmpdump
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libx11
