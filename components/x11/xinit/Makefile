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

X11_CATEGORY=APP
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=           xinit
COMPONENT_VERSION=        1.4.4
COMPONENT_SUMMARY=        xinit - X Window System initializer
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=   sha256:40a47c7a164c7f981ce3787b4b37f7e411fb43231dcde543d70094075dacfef9
COMPONENT_FMRI=           x11/session/xinit
COMPONENT_LICENSE_FILE=   COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+= --with-xinitdir=/etc/X11/xinit

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
