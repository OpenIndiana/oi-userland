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
# Copyright (c) 2016 Sergey Avseyev
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dmenu
COMPONENT_VERSION=	4.6
COMPONENT_PROJECT_URL=	http://tools.suckless.org/dmenu/
COMPONENT_SUMMARY=	dmenu is a dynamic menu for X, originally designed for dwm
COMPONENT_FMRI=		desktop/dmenu
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:4a7a24008a621c3cd656155ad91ab8136db8f0d3b9ec56dafeec518cabda96b3
COMPONENT_ARCHIVE_URL=	http://dl.suckless.org/tools/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	MIT/X
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV=	CC_BITS=$(CC_BITS) LD_BITS=$(LD_BITS)
COMPONENT_BUILD_ARGS=	CC=$(CC)
COMPONENT_INSTALL_ARGS.64=	MACH64=$(MACH64)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxinerama
