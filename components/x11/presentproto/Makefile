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

COMPONENT_NAME=         presentproto
COMPONENT_VERSION=      1.0
COMPONENT_PROJECT_URL=  http://www.freedektop.org/
COMPONENT_SUMMARY=      X11 Present protocol specification
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
	sha256:4519fc0873a92016456e67d160647ff92b6e47fb62317916d61869b916875c4c


COMPONENT_ARCHIVE_URL=  http://xorg.freedesktop.org/releases/individual/proto/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= x11/library/presentproto
COMPONENT_CLASSIFICATION = System/X11
COMPONENT_LICENSE = MIT
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

