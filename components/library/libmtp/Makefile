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
# Copyright 2017 Alexander Pyhalov
#
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libmtp
COMPONENT_VERSION=	1.1.17
COMPONENT_SUMMARY=	libmtp is an Initiator implementation of the Media Transfer Protocol
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_PROJECT_URL=	http://libmtp.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f8a34cf52d9f9b9cb8c7f26b12da347d4af7eb904c13189602e4c6b62d1a79dc
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/libmtp/files/libmtp/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download/
COMPONENT_FMRI=		library/libmtp
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					libtoolize --copy --force &&\
					aclocal -I m4 &&\
					autoheader &&\
					automake -c -f -a &&\
					autoconf )

CPPFLAGS.32 += -D_FILE_OFFSET_BITS=64
CPPFLAGS = $(CPPFLAGS.$(BITS))

CONFIGURE_OPTIONS  += --sysconfdir=/etc
CONFIGURE_OPTIONS  += --enable-shared
CONFIGURE_OPTIONS  += --disable-static

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
