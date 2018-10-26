# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2017, Aurelien Larcher. All rights reserved.
#

# All X11 components should now prefer 64-bits unless specified

PREFERRED_BITS=64

#
# General macros
#
PKG_X11_VERSION=7.7

#
# Provide macros for commonly used urls
#

XORG_PROJECT_URL = https://www.x.org/
XORG_BASE_URL    = https://www.x.org/releases/individual
SOLARIS_XORG_URL = https://github.com/oracle/solaris-userland

XORG_APP_BASE_URL     = $(XORG_BASE_URL)/app
XORG_DATA_BASE_URL    = $(XORG_BASE_URL)/data
XORG_DOC_BASE_URL     = $(XORG_BASE_URL)/doc
XORG_DRIVER_BASE_URL  = $(XORG_BASE_URL)/driver
XORG_FONT_BASE_URL    = $(XORG_BASE_URL)/font
XORG_LIB_BASE_URL     = $(XORG_BASE_URL)/lib
XORG_PROTO_BASE_URL   = $(XORG_BASE_URL)/proto
XORG_TEST_BASE_URL    = $(XORG_BASE_URL)/test
XORG_UTIL_BASE_URL    = $(XORG_BASE_URL)/util
XORG_XCB_BASE_URL     = $(XORG_BASE_URL)/xcb
XORG_XSERVER_BASE_URL = $(XORG_BASE_URL)/xserver

#
# Define library install paths
#

XORG_LIBDIR.32 = $(USRLIBDIR)/xorg	
XORG_LIBDIR.64 = $(USRLIBDIR)/xorg/$(MACH64)	
XORG_LIBDIR    = $(XORG_LIBDIR.$(BITS))

