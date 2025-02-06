#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2021 Gary Mills
# Copyright (c) 2017 Dariusz Sendkowski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         WindowMaker
COMPONENT_VERSION=      0.96.0
COMPONENT_SUMMARY=      Window Maker is an X11 window manager originally designed to provide integration support for the GNUstep Desktop Environment, although it can run stand alone. In every way possible, it reproduces the elegant look and feel of the NeXTSTEP user interface.
COMPONENT_PROJECT_URL=  https://windowmaker.org
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:4fe130ba23cf4aa21c156ec8f01f748df537d0604ec06c6bbcec896df1926f6d
COMPONENT_ARCHIVE_URL=  https://www.windowmaker.org/pub/source/release/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         desktop/window-manager/wmaker
COMPONENT_CLASSIFICATION=System/X11
COMPONENT_LICENSE=      GPL

COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# GNU gettext is needed
PATH=$(PATH.gnu)

CONFIGURE_OPTIONS += --enable-static=no

# Requires header file WINGsP.h to be compiled before main application build can proceed
COMPONENT_PRE_BUILD_ACTION = \
    ( \
        echo "Running ./configure in source directory..."; \
        cd $(SOURCE_DIR) && ./configure; \
        if [ $$? -eq 0 ]; then \
            echo "Running gmake for WINGsP.h..."; \
            gmake -C $(SOURCE_DIR)/WINGs/WINGs; \
        else \
            echo "Configuration failed, aborting build."; \
            exit 1; \
        fi \
    )

# Required dependencies per WindowMaker documentation: https://www.windowmaker.org/docs/wmaker_install.html
REQUIRED_PACKAGES+= developer/build/autoconf
REQUIRED_PACKAGES+= developer/build/automake
REQUIRED_PACKAGES+= developer/build/libtool

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/imagemagick
REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/giflib
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/libxpm
REQUIRED_PACKAGES += x11/library/libxres
