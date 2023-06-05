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

BUILD_BITS= 64
BUILD_STYLE= cmake
USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		freerdp
COMPONENT_VERSION=	2.10.0
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Remote Desktop Viewer Client
COMPONENT_PROJECT_URL=	https://www.freerdp.com
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:a673d3fc21911dd9f196834f2f3a23c3ebc7e5e4deab2f7686fcec879279e2c1
COMPONENT_ARCHIVE_URL=  https://github.com/FreeRDP/FreeRDP/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		desktop/remote-desktop/freerdp
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	Apache v2.0
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# https://github.com/FreeRDP/FreeRDP/issues/5504
CFLAGS += $(XPG6MODE)

CMAKE_OPTIONS += -DCMAKE_SKIP_RPATH=ON
CMAKE_OPTIONS += -DWITH_ALSA=OFF
CMAKE_OPTIONS += -DWITH_CAIRO=ON
CMAKE_OPTIONS += -DWITH_PCSC=OFF
CMAKE_OPTIONS += -DWITH_CUPS=ON
CMAKE_OPTIONS += -DWITH_PULSE=ON
CMAKE_OPTIONS += -DWITH_OSS=OFF
CMAKE_OPTIONS += -DWITH_SSE2=ON
CMAKE_OPTIONS += -DWITH_LIBRARY_VERSIONING=ON
CMAKE_OPTIONS += -DWITH_OPENSSL=ON
CMAKE_OPTIONS += -DWITH_LIBSYSTEMD=OFF
CMAKE_OPTIONS += -DWITH_CLIENT=ON
CMAKE_OPTIONS += -DWITH_SERVER=ON
CMAKE_OPTIONS += -DCHANNEL_GEOMETRY=ON
CMAKE_OPTIONS += -DWITH_CHANNELS=ON
CMAKE_OPTIONS += -DBUILTIN_CHANNELS=OFF
CMAKE_OPTIONS += -DWITH_DIRECTFB=OFF
CMAKE_OPTIONS += -DWITH_GSTREAMER_1_0=ON
CMAKE_OPTIONS += -DWITH_GSTREAMER_0_10=OFF
CMAKE_OPTIONS += -DWITH_ICU=ON
CMAKE_OPTIONS += -DWITH_IPP=OFF
CMAKE_OPTIONS += -DWITH_JPEG=ON
CMAKE_OPTIONS += -DWITH_LAME=ON
CMAKE_OPTIONS += -DWITH_MANPAGES=ON
CMAKE_OPTIONS += -DWITH_ZLIB=ON
CMAKE_OPTIONS += -DWITH_X11=ON
CMAKE_OPTIONS += -DWITH_XCURSOR=ON
CMAKE_OPTIONS += -DWITH_XEXT=ON
CMAKE_OPTIONS += -DWITH_XKBFILE=ON
CMAKE_OPTIONS += -DWITH_XI=ON
CMAKE_OPTIONS += -DWITH_XINERAMA=ON
CMAKE_OPTIONS += -DWITH_XRENDER=ON
CMAKE_OPTIONS += -DWITH_WAYLAND=OFF
CMAKE_OPTIONS += -DWITH_XV=ON

# dependencies on encumbered packages
CMAKE_OPTIONS += -DWITH_GSM=OFF
CMAKE_OPTIONS += -DWITH_X264=OFF
CMAKE_OPTIONS += -DWITH_OPENH264=OFF
CMAKE_OPTIONS += -DWITH_FFMPEG=OFF

# https://github.com/FreeRDP/FreeRDP/issues/4348
# GSS API is not detected correctly anyway
CMAKE_OPTIONS += -DWITH_KRB5=ON
CMAKE_OPTIONS += -DWITH_GSSAPI=OFF

LIBFREERDP2_LIBDIR = /usr/lib/$(MACH64)/freerdp2

COMPONENT_POST_INSTALL_ACTION  = \
    for file in $(PROTO_DIR)/usr/bin/freerdp-proxy $(PROTO_DIR)/usr/lib/$(MACH64)/freerdp2/liburbdrc-client-libusb.so; do \
        /usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(GCC_LIBDIR):$(LIBFREERDP2_LIBDIR)"' $$file ; \
        /usr/bin/elfedit -e 'dyn:value -s  RPATH "$(GCC_LIBDIR):$(LIBFREERDP2_LIBDIR)"' $$file ; \
    done ;

# Auto-generated dependencies
REQUIRED_PACKAGES += audio/lame
REQUIRED_PACKAGES += image/library/libjpeg6
REQUIRED_PACKAGES += image/library/libjpeg6-ijg
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += system/library
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
