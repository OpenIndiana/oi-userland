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
# Copyright (c) 2019 Michal Nowak
# Copyright (c) 2020 Andreas Wacknitz
#

BUILD_BITS=			64
BUILD_STYLE=		meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		desktop-file-utils
COMPONENT_VERSION=	0.26
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/wiki/Software/desktop-file-utils/
COMPONENT_SUMMARY=	A few command line utilities for working with desktop entries
COMPONENT_FMRI=		library/desktop/desktop-file-utils
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Scripts
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:b26dbde79ea72c8c84fb7f9d870ffd857381d049a86d25e0038c4cef4c747309
COMPONENT_ARCHIVE_URL=	https://www.freedesktop.org/software/desktop-file-utils/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_LICENSE=	GPLv2

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
