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
# Copyright 2016 Gary Mills
# Copyright 2015 Alexander Pyhalov
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libmtp
COMPONENT_VERSION=	1.1.11
COMPONENT_SUMMARY=	libmtp is an Initiator implementation of the Media Transfer Protocol
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_PROJECT_URL=	http://libmtp.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:15d96dff79a4f7ad14338894a4096d4ac584c6ad25fdcca955bc4726303287e9
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/libmtp/files/libmtp/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/libmtp
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

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


# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)
