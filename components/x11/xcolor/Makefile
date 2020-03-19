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

BUILD_BITS=64
BUILD_STYLE=justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           xcolor
COMPONENT_VERSION=        7.5
COMPONENT_REVISION=       1
COMPONENT_FMRI=           x11/xcolor
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  xcolor - colormap display program
COMPONENT_SRC=      src
COMPONENT_PROJECT_URL = https://hg.java.net/hg/solaris-x11~x-s12-clone
COMPONENT_LICENSE=      Oracle

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_COMMON_ENV= CC=$(CC)
COMPONENT_COMMON_ENV+= CFLAGS="$(CFLAGS)"
COMPONENT_COMMON_ENV+= LDFLAGS="$(LDFLAGS)"

COMPONENT_BUILD_ENV+= $(COMPONENT_COMMON_ENV)
COMPONENT_BUILD_ARGS= VPATH=$(SOURCE_DIR) -f $(SOURCE_DIR)/Makefile
COMPONENT_INSTALL_ENV+= INSTALL=$(INSTALL)
COMPONENT_INSTALL_ENV+= DESTDIR=$(PROTO_DIR)
COMPONENT_INSTALL_ENV+= bindir=$(USRBINDIR)
COMPONENT_INSTALL_ENV+= mandir=$(USRSHAREMANDIR)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
