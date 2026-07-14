#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2019 Michal Nowak
# Copyright 2020 Marco van Wieringen
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		freerdp
COMPONENT_VERSION=	3.29.0
COMPONENT_SUMMARY=	Remote Desktop Viewer Client
COMPONENT_PROJECT_URL=	https://www.freerdp.com
COMPONENT_SRC=          FreeRDP-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:3d08346b81702c1f431c3aef64628df7911f5c9fd49660f6fbea9bc60ff9a82c
COMPONENT_ARCHIVE_URL=  https://github.com/FreeRDP/FreeRDP/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		desktop/remote-desktop/freerdp
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	Apache v2.0
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# https://github.com/FreeRDP/FreeRDP/issues/5504
CFLAGS += $(XPG6MODE)

CFLAGS += -I$(OPENSSL_INCDIR)
LDFLAGS  += -L$(OPENSSL_LIBDIR)
LDFLAGS  += -L/usr/heimdal/lib/$(MACH64)
LDFLAGS  += -R/usr/heimdal/lib/$(MACH64)

# freerdp-3.22.0/libfreerdp/utils/passphrase.c:319:17: error: implicit declaration of function 'cfmakeraw' [-Wimplicit-function-declaration]
CFLAGS += -Wno-error=implicit-function-declaration

ifeq ($(strip $(MACH)),i386)
CMAKE_OPTIONS += -DWITH_SSE2=ON
else
CMAKE_OPTIONS += -DWITH_SSE2=OFF
endif

CMAKE_OPTIONS += -DBUILTIN_CHANNELS=OFF
CMAKE_OPTIONS += -DCMAKE_SKIP_RPATH=ON
CMAKE_OPTIONS += -DCHANNEL_GEOMETRY=ON
CMAKE_OPTIONS += -DWITH_ALSA=OFF
CMAKE_OPTIONS += -DWITH_CAIRO=ON
CMAKE_OPTIONS += -DWITH_CHANNELS=ON
CMAKE_OPTIONS += -DWITH_CLIENT=ON
CMAKE_OPTIONS += -DWITH_CLIENT_SDL2=ON
CMAKE_OPTIONS += -DWITH_CLIENT_SDL3=OFF
CMAKE_OPTIONS += -DWITH_CUPS=ON
CMAKE_OPTIONS += -DWITH_DIRECTFB=OFF
CMAKE_OPTIONS += -DWITH_FUSE=OFF
CMAKE_OPTIONS += -DWITH_GSTREAMER_1_0=ON
CMAKE_OPTIONS += -DWITH_LIBSYSTEMD=OFF
CMAKE_OPTIONS += -DWITH_ICU=ON
CMAKE_OPTIONS += -DWITH_IPP=OFF
CMAKE_OPTIONS += -DWITH_JPEG=ON
CMAKE_OPTIONS += -DWITH_LAME=ON
CMAKE_OPTIONS += -DWITH_LIBRARY_VERSIONING=ON
CMAKE_OPTIONS += -DWITH_MANPAGES=ON
CMAKE_OPTIONS += -DWITH_OPENSSL=ON
CMAKE_OPTIONS += -DWITH_OSS=OFF
CMAKE_OPTIONS += -DWITH_PCSC=OFF
CMAKE_OPTIONS += -DWITH_PULSE=ON
CMAKE_OPTIONS += -DWITH_SERVER=ON
CMAKE_OPTIONS += -DWITH_WAYLAND=OFF
CMAKE_OPTIONS += -DWITH_X11=ON
CMAKE_OPTIONS += -DWITH_XCURSOR=ON
CMAKE_OPTIONS += -DWITH_XEXT=ON
CMAKE_OPTIONS += -DWITH_XKBFILE=ON
CMAKE_OPTIONS += -DWITH_XI=ON
CMAKE_OPTIONS += -DWITH_XINERAMA=ON
CMAKE_OPTIONS += -DWITH_XRENDER=ON
CMAKE_OPTIONS += -DWITH_XV=ON
CMAKE_OPTIONS += -DWITH_ZLIB=ON

# dependencies on encumbered packages
CMAKE_OPTIONS += -DWITH_DSP_FFMPEG=OFF
CMAKE_OPTIONS += -DWITH_FFMPEG=OFF
CMAKE_OPTIONS += -DWITH_GSM=OFF
CMAKE_OPTIONS += -DWITH_OPENH264=OFF
CMAKE_OPTIONS += -DWITH_MEDIA_FOUNDATION=OFF
CMAKE_OPTIONS += -DWITH_SWSCALE=OFF
CMAKE_OPTIONS += -DWITH_VIDEO_FFMPEG=OFF
CMAKE_OPTIONS += -DWITH_X264=OFF

# Use heimdal Kerberos
CMAKE_OPTIONS += -DKRB5_ROOT_CONFIG=/usr/heimdal/bin/krb5-config
CMAKE_OPTIONS += -DKRB5_ROOT_FLAVOUR=Heimdal

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += audio/lame
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += image/library/sdl2-ttf
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/jansson
REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += library/opus
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/sdl2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/heimdal
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxkbfile
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/libxtst
