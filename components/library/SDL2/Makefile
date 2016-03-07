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
COMPONENT_VERSION=	2.0.4
COMPONENT_PROJECT_URL=	http://www.libsdl.org/
COMPONENT_SUMMARY=	libsdl2 - Simple DirectMedia Layer 2.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:da55e540bf6331824153805d58b590a29c39d2d506c6d02fa409aedeab21174b
COMPONENT_ARCHIVE_URL=	http://www.libsdl.org/release/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI =	library/sdl2
# Note: license change from LGPL was significant in 2.x vs 1.x series, and now
# static linking is permitted. See e.g. https://wiki.libsdl.org/Installation
COMPONENT_LICENSE=	ZLIB
COMPONENT_LICENSE_FILE=	COPYING.txt
COMPONENT_CLASSIFICATION =	System/Libraries

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION = \
			( cd $(@D) && $(CONFIG_SHELL) autogen.sh )

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
