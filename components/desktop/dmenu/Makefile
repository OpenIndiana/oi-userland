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
# Copyright 2020 Andreas Wacknitz
# Copyright 2022 Benjamin S. Osenbach
#
BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dmenu
COMPONENT_VERSION=	5.4
COMPONENT_SUMMARY=	dmenu is a dynamic menu for X, originally designed for dwm
COMPONENT_PROJECT_URL=	https://tools.suckless.org/dmenu/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:8fbace2a0847aa80fe861066b118252dcc7b4ca0a0a8f3a93af02da8fb6cd453
COMPONENT_ARCHIVE_URL=	https://dl.suckless.org/tools/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		desktop/dmenu
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	MIT/X
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxinerama
