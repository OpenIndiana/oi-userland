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
# Copyright (c) 2014 Alexander Pyhalov. All rights reserved
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		sound-theme-freedesktop
COMPONENT_VERSION=	0.6
COMPONENT_PROJECT_URL=	http://www.freedesktop.org/wiki/Specifications/sound-theme-spec/
COMPONENT_SUMMARY=	XDG FreeDesktop Sound Theme
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:b9c052ec28c1cda6fccca6c138934a2527e89f862933eab84b211436668f47d9
COMPONENT_ARCHIVE_URL=	http://0pointer.de/public/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_ENV+=  PERL=$(PERL)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
