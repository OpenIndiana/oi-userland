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

COMPONENT_NAME=		dosbox
COMPONENT_VERSION=	0.74
COMPONENT_PROJECT_URL=	http://www.dosbox.com/
COMPONENT_SUMMARY=	DosBox - DOS Emulator
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:13f74916e2d4002bad1978e55727f302ff6df3d9be2f9b0e271501bd0a938e05
COMPONENT_ARCHIVE_URL=	http://prdownloads.sourceforge.net/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_FMRI=		runtime/dosbox
COMPONENT_CLASSIFICATION=	Applications/System Utilities

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && \
                          aclocal -I. && \
                          autoheader && \
                          libtoolize --automake --copy --force && \
                          automake -a -f -c && \
                          autoconf )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc

CONFIGURE_ENV+=	PERL=$(PERL)
CONFIGURE_ENV+=	PYTHON=$(PYTHON)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/audio/sdl-sound
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += system/library/gcc-6-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
