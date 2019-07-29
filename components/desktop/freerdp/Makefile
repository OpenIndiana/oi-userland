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
#

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		FreeRDP
COMPONENT_VERSION=	2.0.0
COMPONENT_COMMIT=	e873e4f0042dd157f68ae99adb4dc9dcd167ca29
COMPONENT_SUMMARY=	Remote Desktop Viewer Client
COMPONENT_PROJECT_URL=	http://www.freerdp.com
COMPONENT_FMRI=		desktop/remote-desktop/freerdp
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_COMMIT)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_URL=	https://github.com/FreeRDP/FreeRDP/archive/$(COMPONENT_COMMIT).zip
COMPONENT_ARCHIVE_HASH=	\
	sha256:12374e828745e13f707844c4fc4607094f16513b8b94e6728883690fdb9cdc8e
COMPONENT_LICENSE=	Apache v2.0
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

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

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += audio/lame
REQUIRED_PACKAGES += image/library/libjpeg6
REQUIRED_PACKAGES += image/library/libjpeg6-ijg
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/security/openssl
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
REQUIRED_PACKAGES += x11/library/libxv
