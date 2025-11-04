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
# Copyright 2025 Carsten Grzemba
#

BUILD_STYLE = pkg

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		sunray-essential
COMPONENT_VERSION =		5.4
COMPONENT_REVISION =		5
COMPONENT_SUMMARY =		On OI required packages for Sunray Server Software
COMPONENT_PROJECT_URL =		https://dosc.openindina.org
COMPONENT_FMRI =		consolidation/sunray/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION =	System/Virtualization

include $(WS_MAKE_RULES)/common.mk

# be sure that required packages are installed so the resolver will be successful
install: component-environment-prep

# Auto-generated dependencies
REQUIRED_PACKAGES += audio/lame
REQUIRED_PACKAGES += audio/mpg123/32
REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += codec/flac-15
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/audio/pulseaudio/32
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/expat/32
REQUIRED_PACKAGES += library/glib2/32
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += library/libsndfile/32
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += library/nspr/32
REQUIRED_PACKAGES += library/opus
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/sdl2/32
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += package/rpm
REQUIRED_PACKAGES += system/library/c++/sunpro
REQUIRED_PACKAGES += system/library/fontconfig/32
REQUIRED_PACKAGES += system/library/freetype-2/32
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/mozilla-nss
REQUIRED_PACKAGES += system/library/security/libsasl
REQUIRED_PACKAGES += system/library/usb/libusb
REQUIRED_PACKAGES += x11/keyboard/data-xkb
REQUIRED_PACKAGES += x11/keyboard/xkbcomp
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxau
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxdmcp
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxkbfile
REQUIRED_PACKAGES += x11/library/libxpm
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/libxscrnsaver
REQUIRED_PACKAGES += x11/library/libxv
REQUIRED_PACKAGES += x11/xsetroot
