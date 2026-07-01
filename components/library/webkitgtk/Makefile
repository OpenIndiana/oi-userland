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
# Copyright 2017 Alexander Pyhalov
# Copyright 2020 Michal Nowak
# Copyright 2023 Friedrich Kink
# Copyright 2026 Klaus Ziegler
#

USE_PARALLEL_BUILD = yes
BUILD_STYLE=		cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		webkitgtk
COMPONENT_VERSION=	2.52.4
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Web content engine library for GTK+
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:cf4076a1ca2a64788edca8c452d8ebb68d5e2965e588fe46a388a016513edce4
COMPONENT_ARCHIVE_URL=	https://webkitgtk.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://webkitgtk.org
COMPONENT_FMRI=		library/desktop/webkitgtk2
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	BSD,LGPLv2,CCASA3.0
COMPONENT_LICENSE_FILE=	webkitgtk.license

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk
include $(WS_MAKE_RULES)/ninja.mk

PATH= $(PATH.gnu)

COMPONENT_PRE_BUILD_ACTION += $(GSED) -i -e 's:/usr/bin/unifdef:/usr/gnu/bin/unifdef:' $(@D)/build.ninja

LDFLAGS += -lm -lsocket

CMAKE_OPTIONS += -DPORT=GTK
CMAKE_OPTIONS += -GNinja
CMAKE_OPTIONS += -DENABLE_INTROSPECTION=on
CMAKE_OPTIONS += -DENABLE_WEB_RTC=off
CMAKE_OPTIONS += -DENABLE_GEOLOCATION=on
CMAKE_OPTIONS += -DENABLE_SAMPLING_PROFILER=off
CMAKE_OPTIONS += -DENABLE_WEB_AUDIO=on
# CMAKE_OPTIONS += -DENABLE_2022_GLIB_API=off
CMAKE_OPTIONS += -DENABLE_JOURNALD_LOG=off
CMAKE_OPTIONS += -DUSE_LIBHYPHEN=off
CMAKE_OPTIONS += -DENABLED_UNIFIED_BUILDS=OFF
CMAKE_OPTIONS += -DUSE_GBM=off
CMAKE_OPTIONS += -DUSE_GTK4=off
CMAKE_OPTIONS += -DUSE_JPEGXL=off
CMAKE_OPTIONS += -DUSE_GSTREAMER_GL=ON
CMAKE_OPTIONS += -DENABLE_ENCRYPTED_MEDIA=ON
CMAKE_OPTIONS += -DUSE_AVIF=off
CMAKE_OPTIONS += -DUSE_GSTREAMER_TRANSCODER=off
CMAKE_OPTIONS += -DUSE_GSTREAMER_WEBRTC=off
CMAKE_OPTIONS += -DUSE_SYSTEM_MALLOC=on
CMAKE_OPTIONS += -DENABLE_GAMEPAD=off
CMAKE_OPTIONS += -DUSE_WOFF2=off
CMAKE_OPTIONS += -DENABLE_JIT=on
CMAKE_OPTIONS += -DUSE_WPE_RENDERER=OFF
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DUSE_LIBDRM=off
CMAKE_OPTIONS += -DENABLE_SPEECH_SYNTHESIS=off
CMAKE_OPTIONS += -DUSE_LIBBACKTRACE=off
CMAKE_OPTIONS += -DUSE_SYSTEM_SYSPROF_CAPTURE=NO
CMAKE_OPTIONS += -DUSE_SYSPROF_CAPTURE=NO

# Tell g-ir-scanner not to cache results in homedir of user running the build
COMPONENT_BUILD_ENV += GI_SCANNER_DISABLE_CACHE=""

COMPONENT_INSTALL_ARGS = 

# manual dependencies for SPARC
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf

# Build time dependencies
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += developer/gperf
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/python/gi-docgen
REQUIRED_PACKAGES += library/python/pygobject
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += developer/unifdef

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += gnome/accessibility/at-spi2-core
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/base
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += library/libsoup3
REQUIRED_PACKAGES += library/libtasn1
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += x11/library/libepoxy
REQUIRED_PACKAGES += x11/library/libx11
