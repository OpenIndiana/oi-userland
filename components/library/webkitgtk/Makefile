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
# Copyright 2021 Klaus Ziegler
# Copyright 2023 Friedrich Kink
#

USE_PARALLEL_BUILD = yes
BUILD_STYLE=		cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		webkitgtk
COMPONENT_VERSION=	2.42.5
COMPONENT_SUMMARY=	Web content engine library for GTK+
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:b64278c1f20b8cfdbfb5ff573c37d871aba74a1db26d9b39f74e8953fe61e749
COMPONENT_ARCHIVE_URL=	https://webkitgtk.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://webkitgtk.org
COMPONENT_FMRI=		library/desktop/webkitgtk2
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	BSD,LGPLv2,CCASA3.0
COMPONENT_LICENSE_FILE=	webkitgtk.license

UNIFDEF_VER= 2.12
UNIFDEF_DIR= unifdef-$(UNIFDEF_VER)
UNIFDEF_ARCHIVE= $(UNIFDEF_DIR).tar.gz
UNIFDEF_URL= https://dotat.at/prog/unifdef/$(UNIFDEF_ARCHIVE)
UNIFDEF_HASH= sha256:fba564a24db7b97ebe9329713ac970627b902e5e9e8b14e19e024eb6e278d10b

ifeq ($(MACH), sparc)
ADDITIONAL_PATCHES += patches/mapfile.$(MACH)
endif
ifeq ($(MACH), i386)
ADDITIONAL_PATCHES += patches/mapfile.$(MACH)
endif

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk
include $(WS_MAKE_RULES)/ninja.mk

PATH= $(PATH.gnu)

COMPONENT_PRE_BUILD_ACTION += $(GSED) -i -e 's:/usr/bin/unifdef:$(COMPONENT_DIR)/$(UNIFDEF_DIR)/unifdef:' $(@D)/build.ninja

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

LDFLAGS += -lm -lsocket

CMAKE_OPTIONS += -DPORT=GTK
CMAKE_OPTIONS += -GNinja
CMAKE_OPTIONS += -DENABLE_INTROSPECTION=on
CMAKE_OPTIONS += -DENABLE_WEB_RTC=off
CMAKE_OPTIONS += -DENABLE_GEOLOCATION=on
CMAKE_OPTIONS += -DENABLE_SAMPLING_PROFILER=off
CMAKE_OPTIONS += -DENABLE_WEB_AUDIO=on
CMAKE_OPTIONS += -DENABLE_2022_GLIB_API=off
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
CMAKE_OPTIONS += -DCMAKE_INSTALL_LIBEXECDIR:PATH=lib
CMAKE_OPTIONS += -DUSE_WPE_RENDERER=off
CMAKE_OPTIONS += -DENABLE_GAMEPAD=off
CMAKE_OPTIONS += -DUSE_WOFF2=off
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DJPEG_INCLUDE_DIR=$(JPEG_INCDIR)
CMAKE_OPTIONS += -DJPEG_LIBRARY=$(JPEG_LIBDIR)/libjpeg.so

# Tell g-ir-scanner not to cache results in homedir of user running the build
COMPONENT_BUILD_ENV += GI_SCANNER_DISABLE_CACHE=""

COMPONENT_INSTALL_ARGS = 

download:: $(UNIFDEF_DIR)/unifdef

$(UNIFDEF_ARCHIVE):
	$(FETCH) --file $(UNIFDEF_ARCHIVE) --url $(UNIFDEF_URL) --hash $(UNIFDEF_HASH)

$(UNIFDEF_DIR)/unifdef: $(UNIFDEF_ARCHIVE)
	$(GTAR) xzf $(UNIFDEF_ARCHIVE)
	$(RM) -r $(UNIFDEF_ARCHIVE)
	( cd $(UNIFDEF_DIR); CC=$(CC) gmake )
	test -x $(UNIFDEF_DIR)/unifdef || exit 1

CLEAN_PATHS += $(UNIFDEF_DIR)

# Buld time dependencies
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += developer/gperf
REQUIRED_PACKAGES += library/gnutls-3

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/openjpeg
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
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
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxdamage
