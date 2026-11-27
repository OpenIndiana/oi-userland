#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2026 isoriano1968
#

BUILD_BITS=		NO_ARCH
BUILD_STYLE=		meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cantarell-fonts
HUMAN_VERSION=		0.301
COMPONENT_VERSION_MAJOR=	$(HUMAN_VERSION)
COMPONENT_SUMMARY=	Cantarell, a contemporary humanist sans serif font
COMPONENT_ARCHIVE_HASH=	\
	sha256:3d35db0ac03f9e6b0d5a53577591b714238985f4cfc31a0aa17f26cd74675e83
COMPONENT_FMRI=		system/font/truetype/cantarell
COMPONENT_CLASSIFICATION=	System/Fonts
COMPONENT_LICENSE=	OFL-1.1
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is expected
PATH=			$(PATH.gnu)

CONFIGURE_OPTIONS +=	-Dfontsdir=/usr/share/fonts/TrueType/cantarell

# Auto-generated dependencies
