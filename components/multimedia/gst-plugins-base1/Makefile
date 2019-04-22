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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gst-plugins-base1
COMPONENT_VERSION= 1.14.4
COMPONENT_SUMMARY= GNOME streaming media framework plugins
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_FMRI= library/audio/gstreamer1/plugin/base
COMPONENT_SRC_NAME= gst-plugins-base
COMPONENT_SRC= $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:ca6139490e48863e7706d870ff4e8ac9f417b56f3b9e4b3ce490c13b09a77461
COMPONENT_ARCHIVE_URL= \
  http://gstreamer.freedesktop.org/src/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= http://gstreamer.freedesktop.org/
COMPONENT_LICENSE= GPLv2,LGPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

gcc_OPT = -O2

PATH = $(PATH.gnu)

CFLAGS += -I/usr/sfw/include -I/usr/X11/include

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/$(MACH64)
CONFIGURE_OPTIONS += --enable-orc
CONFIGURE_OPTIONS += --enable-pango
CONFIGURE_OPTIONS += --disable-gles2
CONFIGURE_OPTIONS += --enable-external
CONFIGURE_OPTIONS += --enable-experimental
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --disable-alsa
CONFIGURE_OPTIONS += --with-default-audiosrc=autoaudiosrc
CONFIGURE_OPTIONS += --with-default-audiosink=autoaudiosink
CONFIGURE_OPTIONS += --with-default-videosink=autovideosink

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_INSTALL_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ENV += CC="$(CC)"

unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS= \
	'-n ' \
	'-e "/TOTAL/p" ' \
	'-e "/PASS/p" '  \
	'-e "/SKIP/p" '  \
	'-e "/XFAIL/p" ' \
	'-e "/FAIL/p" '  \
	'-e "/XPASS/p" ' \
	'-e "/ERROR/p" '

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Build dependencies
REQUIRED_PACKAGES += x11/library/mesa

# Auto-generated dependencies
REQUIRED_PACKAGES += codec/libtheora
REQUIRED_PACKAGES += image/library/libjpeg6
REQUIRED_PACKAGES += image/library/libjpeg6-ijg
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
REQUIRED_PACKAGES += x11/library/libxv
