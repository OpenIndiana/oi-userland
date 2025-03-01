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
# Copyright 2022 Niklas Poslovski
#

BUILD_STYLE= cmake
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=         pan
COMPONENT_VERSION=      0.162
COMPONENT_SUMMARY=      A powerful Newsgroup Article reader
COMPONENT_PROJECT_URL=  https://pan.rebelbase.com
COMPONENT_SRC=          $(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:f33b136621f7c0e7feac9ed6d0ff3fe15013335a100cb48b4151f4528be10059
COMPONENT_ARCHIVE_URL=	https://gitlab.gnome.org/GNOME/pan/-/archive/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         desktop/nntp/pan
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -lsocket -lnsl

CMAKE_OPTIONS += -DWANT_GKR=ON

# SPARC needs math library
ifeq ($(strip $(MACH)),sparc)
REQUIRED_PACKAGES += system/library/math
endif

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gspell-3
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gmime3
REQUIRED_PACKAGES += library/gnome/gcr
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
