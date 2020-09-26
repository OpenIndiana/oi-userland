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
# Copyright (c) 2020 Andreas Wacknitz
#

BUILD_BITS=			32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		SDL2
COMPONENT_VERSION=	2.0.12
COMPONENT_PROJECT_URL=	https://www.libsdl.org/
COMPONENT_SUMMARY=	libsdl2 - Simple DirectMedia Layer 2.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:349268f695c02efbc9b9148a70b85e58cefbbf704abd3e91be654db7f1e2c863
COMPONENT_ARCHIVE_URL=	https://www.libsdl.org/release/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI =	library/sdl2
# Note: license change from LGPL was significant in 2.x vs 1.x series, and now
# static linking is permitted. See e.g. https://wiki.libsdl.org/Installation
COMPONENT_LICENSE=	ZLIB
COMPONENT_LICENSE_FILE=	COPYING.txt
COMPONENT_CLASSIFICATION =	System/Libraries

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = \
			( cd $(@D) && $(CONFIG_SHELL) autogen.sh )

CONFIGURE_OPTIONS += --disable-rpath

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
