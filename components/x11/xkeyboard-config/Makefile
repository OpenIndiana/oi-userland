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
#

include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=           xkeyboard-config
COMPONENT_VERSION=        2.30
COMPONENT_FMRI=           x11/keyboard/data-xkb
COMPONENT_SUMMARY=        X Keyboard Configuration Database
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_PROJECT_URL=    https://freedesktop.org/wiki/Software/XKeyboardConfig/
COMPONENT_ARCHIVE_URL= \
	https://www.x.org/releases/individual/data/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
	sha256:095a524f7b633ed257617202d06c9c71fe020c8897b106cf0dcdd0c6e8b797d4
COMPONENT_LICENSE=        MIT


include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += text/intltool
REQUIRED_PACKAGES += x11/keyboard/xkbcomp
