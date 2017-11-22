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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		SDL
COMPONENT_VERSION=	1.2.15
COMPONENT_REVISION=	3
COMPONENT_PROJECT_URL=	http://www.libsdl.org/
COMPONENT_SUMMARY=	libsdl - Simple DirectMedia Layer
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:d6d316a793e5e348155f0dd93b979798933fb98aa1edebcc108829d6474aad00
COMPONENT_ARCHIVE_URL=	http://www.libsdl.org/release/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/sdl
COMPONENT_LICENSE =	LGPLv2.1
COMPONENT_LICENSE_FILE =	COPYING
COMPONENT_CLASSIFICATION =	System/Libraries

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					$(CONFIG_SHELL) autogen.sh )



CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--disable-assembly
CONFIGURE_OPTIONS +=	--disable-rpath

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
