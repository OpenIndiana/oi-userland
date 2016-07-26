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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= webkitgtk
COMPONENT_VERSION= 2.12.2
COMPONENT_SUMMARY= Web content engine library for GTK+
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:9dc49b908b1c37da739703e1402a7f07c4ea9093b8ecfb34f20e8f74e328f124
COMPONENT_ARCHIVE_URL= \
  http://webkitgtk.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org
COMPONENT_FMRI= library/desktop/webkitgtk2
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE= BSD, LGPLv2,CCASA3.0
COMPONENT_LICENSE_FILE = webkitgtk.license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

LDFLAGS+=-lm -lsocket

CMAKE_OPTIONS += -DPORT=GTK
CMAKE_OPTIONS += -DENABLE_INTROSPECTION=off
CMAKE_OPTIONS += -DENABLE_CREDENTIAL_STORAGE=off
CMAKE_OPTIONS += -DENABLE_GEOLOCATION=off
CMAKE_OPTIONS += -DENABLE_SAMPLING_PROFILER=off
CMAKE_OPTIONS += -DENABLE_WEB_AUDIO=off
CMAKE_OPTIONS += -DENABLE_VIDEO=off
CMAKE_OPTIONS += -DUSE_LIBHYPHEN=off
CMAKE_OPTIONS += -DUSE_LIBNOTIFY=on
CMAKE_OPTIONS += -DUSE_SYSTEM_MALLOC=on
CMAKE_OPTIONS += -DLIBEXECDIR=/usr/lib
CMAKE_OPTIONS += -DCMAKE_INSTALL_LIBEXECDIR:PATH=lib

build: $(BUILD_32)

install: $(INSTALL_32)

REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/gperf
REQUIRED_PACKAGES += image/library/libjpeg6-ijg
REQUIRED_PACKAGES += image/library/libjpeg6
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/gcc-4-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxdamage
