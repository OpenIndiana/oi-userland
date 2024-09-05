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
# Copyright 2019 Michal Nowak
# Copyright 2023 Friedrich Kink
#

BUILD_STYLE= meson
DEFAULT_COMPONENT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         cairo
COMPONENT_VERSION=      1.18.2
COMPONENT_SUMMARY=      Vector graphics library
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:a62b9bb42425e844cc3d6ddde043ff39dbabedd1542eba57a2eb79f85889d45a
COMPONENT_ARCHIVE_URL=  https://cairographics.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://cairographics.org/
COMPONENT_FMRI=         library/desktop/cairo
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Libraries
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING-LGPL-2.1

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)
# to avoid the following error
# ld: fatal: recording name conflict: file 'src/libcairo.so.2.11800.0' and file '/usr/lib/amd64/libcairo.so' provide identical dependency names: libcairo.so.2
# ld: fatal: file processing errors. No output written to test/any2ppm
COMPONENT_POST_CONFIGURE_ACTION= $(GSED) -i -e '/^ LINK_ARGS/s:/usr/lib/amd64/libcairo.so :$(@D)/src/libcairo.so :'  $(@D)/build.ninja
COMPONENT_BUILD_ARGS= -j1

LDFLAGS += -lsocket

COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9]\.[0-9]*s//" '
COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9]*\.[0-9]*s//" '

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += library/lzo
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrender
