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
# Copyright 2015 Alexander Pyhalov
# Copyright 2020 Andreas Wacknitz
#

BUILD_BITS= 64_and_32
DROP_STATIC_LIBRARIES = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= lame
COMPONENT_VERSION= 4.0
COMPONENT_SUMMARY= LAME is a high quality MPEG Audio Layer III (MP3) encoder licensed under the LGPL 
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:3df5124d5ad3a98312ffd7ba6a9b36230e4f8a3e66d3ce0f425e336c32d216eb
COMPONENT_ARCHIVE_URL= https://downloads.sourceforge.net/sourceforge/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://lame.sourceforge.io/
COMPONENT_LICENSE= LGPL-2.0-only
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_CLASSIFICATION= System/Media
COMPONENT_FMRI= audio/lame

COMPONENT_FMRI.lame-32 =	$(COMPONENT_FMRI)/32
COMPONENT_SUMMARY.lame-32 =	$(COMPONENT_SUMMARY) (32-bit)

include $(WS_MAKE_RULES)/common.mk

CFLAGS += -Wno-incompatible-pointer-types
CFLAGS += -Wno-error=implicit-function-declaration

CONFIGURE_OPTIONS += --with-fileio=sndfile
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-rpath

# We do not need 32 bit lame frontend
CONFIGURE_OPTIONS.32 += --disable-frontend

# Auto-generated dependencies
REQUIRED_PACKAGES += audio/mpg123
REQUIRED_PACKAGES += audio/mpg123/32
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
