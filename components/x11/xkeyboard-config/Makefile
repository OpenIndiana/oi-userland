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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           xkeyboard-config
COMPONENT_VERSION=        2.20
COMPONENT_REVISION=       2
COMPONENT_SUMMARY=        X Keyboard Configuration Database
COMPONENT_PROJECT_URL=    https://freedesktop.org/wiki/Software/XKeyboardConfig/
COMPONENT_FMRI=           x11/keyboard/data-xkb
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SRC=		  $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL= \
  http://www.x.org/releases/individual/data/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:d1bfc72553c4e3ef1cd6f13eec0488cf940498b612ab8a0b362e7090c94bc134
COMPONENT_LICENSE=        MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

REQUIRED_PACKAGES += text/intltool
REQUIRED_PACKAGES += x11/keyboard/xkbcomp
