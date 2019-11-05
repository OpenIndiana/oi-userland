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
# Copyright 2019 Aurelien Larcher
#

BUILD_BITS=32_and_64
BUILD_STYLE=justmake
COMPONENT_X11_DEFAULTS=no
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=         libxaw5
COMPONENT_VERSION=      $(PKG_X11_VERSION)
COMPONENT_FMRI=         x11/library/toolkit/libxaw5
COMPONENT_CLASSIFICATION=System/X11
COMPONENT_SUMMARY=      libXaw5 - X Athena Widgets Toolkit (X11R5/X11R6 binary compatibility version)
COMPONENT_SRC=          src
COMPONENT_PROJECT_URL = https://hg.java.net/hg/solaris-x11~x-s12-clone
COMPONENT_LICENSE=      Oracle

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.illumos)

COMPONENT_COMMON_ENV= CC=$(CC)
COMPONENT_COMMON_ENV+= CPPFLAGS="-I$(SOURCE_DIR) "
COMPONENT_COMMON_ENV+= CFLAGS="$(CFLAGS) "
COMPONENT_COMMON_ENV+= LDFLAGS="$(LDFLAGS)  -Wl,-M,$(COMPONENT_DIR)/mapfile-vers"

COMPONENT_BUILD_ENV+= $(COMPONENT_COMMON_ENV)
COMPONENT_BUILD_ENV+= PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"
COMPONENT_BUILD_ARGS= VPATH=$(SOURCE_DIR) -f $(SOURCE_DIR)/Makefile
COMPONENT_INSTALL_ENV+= INSTALL=$(INSTALL)
COMPONENT_INSTALL_ENV+= DESTDIR=$(PROTO_DIR)
COMPONENT_INSTALL_ENV+= PREFIX=$(USRDIR)
COMPONENT_INSTALL_ENV+= libdir=$(USRLIBDIR.$(BITS))

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxt
