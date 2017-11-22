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
# Copyright (c) 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		SDL2
COMPONENT_VERSION=	2.0.7
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.libsdl.org/
COMPONENT_SUMMARY=	libsdl2 - Simple DirectMedia Layer 2.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:490428b41c3231395d2774dd25cdd6e5e2bae308adc77ebb61219ad49d6537cc
COMPONENT_ARCHIVE_URL=	http://www.libsdl.org/release/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI =	library/sdl2
# Note: license change from LGPL was significant in 2.x vs 1.x series, and now
# static linking is permitted. See e.g. https://wiki.libsdl.org/Installation
COMPONENT_LICENSE=	ZLIB
COMPONENT_LICENSE_FILE=	COPYING.txt
COMPONENT_CLASSIFICATION =	System/Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = \
			( cd $(@D) && $(CONFIG_SHELL) autogen.sh )

CONFIGURE_OPTIONS += --disable-rpath

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
