#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2015 Ken Mays. All Rights Reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libXrandr
COMPONENT_VERSION=      1.4.2
COMPONENT_PROJECT_URL=  http://www.x.org/
COMPONENT_SUMMARY=      X Resize, Rotate and Reflection extension library 
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
	sha256:8898baf09fd8c2eb1ae0a82e24c0522b89f8b91e44d3ce1e8a0f39cc8817d2b6


COMPONENT_ARCHIVE_URL=  http://www.x.org/releases/individual/lib/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= x11/library/libxrandr
COMPONENT_CLASSIFICATION = System/X11
COMPONENT_LICENSE = MIT License (libXrandr)
COMPONENT_LICENSE_FILE = 

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

# CPPFLAGS += "-I/usr/include/pixman-1"

# CONFIGURE_LIBDIR.32 = /usr/lib
# CONFIGURE_LIBDIR.64 = /usr/lib/$(MACH64)

CONFIGURE_OPTIONS+=    

# CONFIGURE_ENV+= CPPFLAGS="$(CPPFLAGS)"
# CONFIGURE_ENV+= MISC_MAN_SUFFIX=3

# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk

