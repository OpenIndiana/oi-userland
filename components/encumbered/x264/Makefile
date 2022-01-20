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
#

BUILD_STYLE=configure
BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         x264
COMPONENT_LIB_VERSION=	164
COMPONENT_SNAPSHOT_DATE= 20211219
X264_COMMIT=19856cc41ad11e434549fb3cc6a019e645ce1efe
COMPONENT_SRC=		$(COMPONENT_NAME)-$(X264_COMMIT)
COMPONENT_VERSION=	0.$(COMPONENT_LIB_VERSION).0.$(COMPONENT_SNAPSHOT_DATE)
COMPONENT_FMRI=         library/video/x264
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_SUMMARY=      H.264 encoder library
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-snapshot-$(COMPONENT_SNAPSHOT_DATE).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:11c050a7e6f095be63344f95d453ce9e46681453305c8ea469bcc9b1a7c14ae2
COMPONENT_ARCHIVE_URL=  \
	https://code.videolan.org/videolan/x264/-/archive/$(X264_COMMIT)/x264-$(X264_COMMIT).tar.gz	
COMPONENT_PROJECT_URL=  http://www.videolan.org/developers/x264.html
COMPONENT_LICENSE=      GPLv2.0
COMPONENT_LICENSE_FILE= COPYING

PKG_MACROS += COMPONENT_LIB_VERSION=$(COMPONENT_LIB_VERSION)

include $(WS_MAKE_RULES)/encumbered.mk
TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

CFLAGS.32 = -D_FILE_OFFSET_BITS=64
CFLAGS += $(CFLAGS.$(BITS))

CONFIGURE_OPTIONS = --prefix=/usr
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --enable-pic
CONFIGURE_OPTIONS += --extra-cflags="$(CFLAGS)"
CONFIGURE_OPTIONS += --extra-ldflags="$(LDFLAGS)"
CONFIGURE_OPTIONS += --disable-cli
CONFIGURE_OPTIONS += --enable-shared

CONFIGURE_ENV.32 = host="i386-pc-solaris2.11"
CONFIGURE_ENV.64 = host="amd64-pc-solaris2.11"
CONFIGURE_ENV += $(CONFIGURE_ENV.$(BITS))




# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
