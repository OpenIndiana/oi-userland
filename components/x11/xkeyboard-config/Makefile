#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Aurelien Larcher
# Copyright 2019 Michal Nowak
# Copyright 2022 Andreas Wacknitz
#
X11_CATEGORY= DATA
BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=         xkeyboard-config
COMPONENT_VERSION=      2.39
COMPONENT_SUMMARY=      X Keyboard Configuration Database
COMPONENT_PROJECT_URL=  https://freedesktop.org/wiki/Software/XKeyboardConfig/
COMPONENT_ARCHIVE_URL=  https://www.x.org/releases/individual/data/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:5ac5f533eff7b0c116805fe254fd79b2c9882700a4f9f2c070f8c4eae5aaa682
COMPONENT_FMRI=         x11/keyboard/data-xkb
COMPONENT_CLASSIFICATION=System/X11
COMPONENT_LICENSE=		MIT
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Manually added build dependencies
REQUIRED_PACKAGES += text/intltool
REQUIRED_PACKAGES += x11/keyboard/xkbcomp

# Auto-generated dependencies
