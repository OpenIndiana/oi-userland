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
# Copyright 2015 Alexander Pyhalov
#

BUILD_BITS=64
BUILD_STYLE=justmake
COMPONENT_X11_DEFAULTS=no
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= mkcookie
COMPONENT_VERSION= 0.5.11
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= utility used to generate fresh 'Magic Cookies'
COMPONENT_SRC= src
COMPONENT_PROJECT_URL = https://hg.java.net/hg/solaris-x11~x-s12-clone
COMPONENT_FMRI= x11/session/mkcookie
COMPONENT_LICENSE= MIT
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_CLASSIFICATION= System/X11

include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -L$(XORG_LIBDIR) -R$(XORG_LIBDIR)

COMPONENT_COMMON_ENV = CC=$(CC)
COMPONENT_COMMON_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_COMMON_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_BUILD_ENV += $(COMPONENT_COMMON_ENV)
COMPONENT_INSTALL_ENV += INSTALL=$(INSTALL)
COMPONENT_INSTALL_ENV += PREFIX=/usr

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libxau
