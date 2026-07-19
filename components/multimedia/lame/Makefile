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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= lame
COMPONENT_VERSION= 3.101
COMPONENT_SUMMARY= LAME is a high quality MPEG Audio Layer III (MP3) encoder licensed under the LGPL 
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:7578af6eebd578b2bd64e468fac4ae1f03670a7e028166e67f855674b9b6aeac
COMPONENT_ARCHIVE_URL= https://downloads.sourceforge.net/sourceforge/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://lame.sourceforge.io/
COMPONENT_LICENSE= LGPLv2
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_CLASSIFICATION= System/Media
COMPONENT_FMRI= audio/lame

include $(WS_MAKE_RULES)/common.mk

CFLAGS += -Wno-incompatible-pointer-types
CFLAGS += -Wno-error=implicit-function-declaration

CONFIGURE_OPTIONS += --with-fileio=sndfile
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-rpath

# Manually added dependencies
REQUIRED_PACKAGES += library/libsndfile/32

# Auto-generated dependencies
REQUIRED_PACKAGES += audio/mpg123
REQUIRED_PACKAGES += audio/mpg123/32
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
