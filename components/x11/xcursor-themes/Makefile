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
# Copyright 2015 Aurelien Larcher
#

X11_CATEGORY= DATA
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=           xcursor-themes
COMPONENT_VERSION=        1.0.7
COMPONENT_SUMMARY=        Cursor themes from X.Org
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=   sha256:95bae8f48823d894a05bf42dfbf453674ab7dbdeb11e2bc079e8525ad47378c8
COMPONENT_FMRI=           x11/data/xcursor-themes
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_LICENSE=        MIT License
COMPONENT_LICENSE_FILE=   COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Build dependencies
REQUIRED_PACKAGES += image/xcursorgen
REQUIRED_PACKAGES += x11/library/libxcursor

# Auto-generated dependencies
