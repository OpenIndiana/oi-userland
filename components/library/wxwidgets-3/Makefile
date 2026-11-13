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
# Copyright 2017 Aurelien Larcher
# Copyright 2019 Michal Nowak
#

USE_PARALLEL_BUILD= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		wxWidgets
COMPONENT_VERSION=	3.2.12
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=      wxWidgets - Cross-Platform GUI Library
COMPONENT_PROJECT_URL=  https://www.wxwidgets.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=  https://github.com/wxWidgets/wxWidgets/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:a62719bb5e1dcc41c1a6fc1eecd499c7ee8521f70402c7b1bb3342a1e16344e0
COMPONENT_FMRI=		library/graphics/wxwidgets-3
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Libraries
COMPONENT_LICENSE=      wxWindows Library license
COMPONENT_LICENSE_FILE= docs/licence.txt

WXWVER = $(subst $(space),.,$(wordlist 1,2,$(subst ., ,$(HUMAN_VERSION))))

COMPONENT_SUMMARY.library=	$(COMPONENT_SUMMARY) (runtime)
COMPONENT_FMRI.library=		library/wxwidgets-$(subst .,,$(WXWVER))

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# We are patching configure.in
COMPONENT_PREP_ACTION += (cd $(@D) && $(ENV) ./autogen.sh) ;

CONFIGURE_OPTIONS += --with-gtk=2
CONFIGURE_OPTIONS += --without-gtkprint
CONFIGURE_OPTIONS += --enable-gui
CONFIGURE_OPTIONS += --enable-xrc
CONFIGURE_OPTIONS += --enable-display
CONFIGURE_OPTIONS += --disable-epollloop
CONFIGURE_OPTIONS += --enable-geometry
CONFIGURE_OPTIONS += --enable-graphics_ctx
CONFIGURE_OPTIONS += --enable-mediactrl
CONFIGURE_OPTIONS += --enable-mimetype
CONFIGURE_OPTIONS += --enable-sound
CONFIGURE_OPTIONS += --enable-unicode
CONFIGURE_OPTIONS += --enable-webview
CONFIGURE_OPTIONS += --disable-xlocale
CONFIGURE_OPTIONS += --with-subdirs
CONFIGURE_OPTIONS += --with-expat
CONFIGURE_OPTIONS += --without-gnomevfs
CONFIGURE_OPTIONS += --with-libjpeg=sys
CONFIGURE_OPTIONS += --with-libpng=sys
CONFIGURE_OPTIONS += --with-regex=sys
CONFIGURE_OPTIONS += --with-libtiff=sys
CONFIGURE_OPTIONS += --without-libmspack
CONFIGURE_OPTIONS += --with-opengl
CONFIGURE_OPTIONS += --with-sdl

# Convert absolute symlink to relative one
COMPONENT_POST_INSTALL_ACTION += \
	$(RM) $(PROTOUSRBINDIR)/wx-config ; \
	$(SYMLINK) ../lib/$(MACH64)/wx/config/gtk2-unicode-$(WXWVER) $(PROTOUSRBINDIR)/wx-config ;

# Replace wxWidgets version number by WXWVER
WXWVER_RE = $(subst .,\.,$(WXWVER))
GENERATE_EXTRA_SED += -e 's/$(WXWVER_RE)/$$(WXWVER)/g'

# WXWVER is needed for manifest processing
PKG_VARS += WXWVER

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/base
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/sdl2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += service/opengl/ogl-select
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxkbcommon
REQUIRED_PACKAGES += x11/library/libxtst
REQUIRED_PACKAGES += x11/library/libxxf86vm
