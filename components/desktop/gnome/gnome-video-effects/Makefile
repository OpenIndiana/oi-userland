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

BUILD_STYLE=		meson

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-video-effects
HUMAN_VERSION=		0.6.0
COMPONENT_SUMMARY=	GStreamer effect descriptions for GNOME camera applications
COMPONENT_ARCHIVE_HASH=	\
	sha256:d7aeaeb46b3f5a832fb2e0d90b42bf8c6160202ca52ac9add17afce192e3c8a8
COMPONENT_FMRI=		library/desktop/gnome-video-effects
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	GPL-2.0-or-later
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is expected
PATH=			$(PATH.gnu)

# Auto-generated dependencies
