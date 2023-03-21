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
# Copyright 2023 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         x264
COMPONENT_LIB_VERSION=	164
COMPONENT_SNAPSHOT_DATE= 20230128
X264_COMMIT=eaa68fad9e5d201d42fde51665f2d137ae96baf0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(X264_COMMIT)
COMPONENT_VERSION=	0.$(COMPONENT_LIB_VERSION).0.$(COMPONENT_SNAPSHOT_DATE)
COMPONENT_FMRI=         library/video/x264
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_SUMMARY=      H.264 encoder library
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-snapshot-$(COMPONENT_SNAPSHOT_DATE).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:580f07f08af23768074e5346bdf32c77b68b4d4e614f4998ea869b02fc29714d
COMPONENT_ARCHIVE_URL=  \
	https://code.videolan.org/videolan/x264/-/archive/$(X264_COMMIT)/x264-$(X264_COMMIT).tar.gz	
COMPONENT_PROJECT_URL=  https://www.videolan.org/developers/x264.html
COMPONENT_LICENSE=      GPLv2.0
COMPONENT_LICENSE_FILE= COPYING

PKG_MACROS += COMPONENT_LIB_VERSION=$(COMPONENT_LIB_VERSION)

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

TEST_TARGET=$(NO_TESTS)

PATH = $(PATH.gnu)

CONFIGURE_OPTIONS = --prefix=/usr
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --enable-pic
CONFIGURE_OPTIONS += --extra-cflags="$(CFLAGS)"
CONFIGURE_OPTIONS += --extra-ldflags="$(LDFLAGS)"
CONFIGURE_OPTIONS += --disable-cli
CONFIGURE_OPTIONS += --enable-shared

CONFIGURE_ENV += host="amd64-pc-solaris2.11"

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
