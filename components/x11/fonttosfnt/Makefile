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
# Copyright 2018 Aurelien Larcher
#

X11_CATEGORY=APP
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=		fonttosfnt
COMPONENT_VERSION=	1.2.2
COMPONENT_SUMMARY=	fonttosfnt - Wrap a bitmap font in a sfnt (TrueType) wrapper
COMPONENT_FMRI=		x11/fonttosfnt
COMPONENT_ARCHIVE_HASH=	sha256:1a1bb4ef25856dea7de3d491ae7231493225b400bee0f6a1f949017ffd203a64

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libfontenc
