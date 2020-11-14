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

COMPONENT_NAME=           fonttosfnt
COMPONENT_VERSION=        1.2.0
COMPONENT_SUMMARY=        fonttosfnt - Wrap a bitmap font in a sfnt (TrueType) wrapper
COMPONENT_FMRI=           x11/fonttosfnt
COMPONENT_ARCHIVE_HASH= \
	sha256:79f35ace377c5409c05ed71f0e8b75f8ca6ddf0a2f6b6d7ecb770ee10072a621

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libfontenc
