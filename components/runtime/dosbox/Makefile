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
# Copyright (c) 2015 Alexander Pyhalov
# Copyright (c) 2019 Michal Nowak
#

BUILD_BITS=			32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dosbox
COMPONENT_VERSION=	0.74-3
COMPONENT_REVISION= 1
IPS_COMPONENT_VERSION=	0.74.3
COMPONENT_PROJECT_URL=	https://www.dosbox.com/
COMPONENT_SUMMARY=	DosBox - DOS Emulator
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:c0d13dd7ed2ed363b68de615475781e891cd582e8162b5c3669137502222260a
COMPONENT_ARCHIVE_URL=	https://prdownloads.sourceforge.net/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_FMRI=		runtime/dosbox
COMPONENT_CLASSIFICATION=	Applications/System Utilities

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( \
	cd $(@D) && \
	aclocal -I. && \
	autoheader && \
	libtoolize --automake --copy --force && \
	automake -a -f -c && \
	autoconf )

CONFIGURE_OPTIONS +=	--sysconfdir=/etc

CONFIGURE_ENV +=	PERL=$(PERL)
CONFIGURE_ENV +=	PYTHON=$(PYTHON)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/audio/sdl-sound
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
