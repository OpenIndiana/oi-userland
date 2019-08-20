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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libXtsol
COMPONENT_SRC= srcs
COMPONENT_VERSION= 0.5.11
COMPONENT_SUMMARY= libXtsol - Solaris Trusted Extensions X11 extension client library
COMPONENT_PROJECT_URL = https://hg.java.net/hg/solaris-x11~x-s12-clone
COMPONENT_CLASSIFICATION= System/Trusted
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = libXtsol.license
COMPONENT_FMRI = x11/trusted/libxtsol

include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

SERVERMOD_SUBDIR.64=/$(MACH64)
SERVERMOD_SUBDIR=$(SERVERMOD_SUBDIR.$(BITS))
X11_SERVERMODS_DIR=/usr/lib/xorg/modules

CPPFLAGS += -I/usr/include/xorg

MACHDIR.64=/$(MACH64)

COMPONENT_COMMON_ENV = CC=$(CC)
COMPONENT_COMMON_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_COMMON_ENV += CPPFLAGS="$(CPPFLAGS)"
COMPONENT_COMMON_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_BUILD_ENV += $(COMPONENT_COMMON_ENV)
COMPONENT_INSTALL_ENV += INSTALL=$(INSTALL)
COMPONENT_INSTALL_ENV += libdir=/usr/lib$(MACHDIR.$(BITS))
COMPONENT_INSTALL_ENV += PREFIX=/usr

download:

clobber: clean

$(SOURCE_DIR)/.prep:
	$(TOUCH) $@

clean::
	$(RM) $(SOURCE_DIR)/.prep

$(BUILD_32_and_64):	Makefile

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
