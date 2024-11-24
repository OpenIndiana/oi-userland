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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libmtp
COMPONENT_VERSION=	1.1.22
COMPONENT_SUMMARY=	libmtp is an Initiator implementation of the Media Transfer Protocol
COMPONENT_PROJECT_URL=	https://libmtp.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:c3fcf411aea9cb9643590cbc9df99fa5fe30adcac695024442973d76fa5f87bc
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/libmtp/files/libmtp/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download/
COMPONENT_FMRI=		library/libmtp
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= ( \
	cd $(@D)  && \
	libtoolize --copy --force && \
	aclocal -I m4 && \
	autoheader && \
	automake -c -f -a && \
	autoconf )

CONFIGURE_OPTIONS  += --enable-shared
CONFIGURE_OPTIONS  += --disable-static
CONFIGURE_OPTIONS  += --disable-dependency-tracking

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
