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

COMPONENT_NAME= xf86-input-hotkey
COMPONENT_SRC= src
COMPONENT_VERSION= 0.5.11
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= xf86-input-hotkey: ACPI hotkey input driver for the Xorg server
COMPONENT_PROJECT_URL = https://hg.java.net/hg/solaris-x11~x-s12-clone
COMPONENT_CLASSIFICATION= Drivers/Other Peripherals
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = xf86-input-hotkey.license
COMPONENT_FMRI = x11/server/xorg/driver/xorg-input-hotkey

include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

SERVERMOD_SUBDIR.64=/$(MACH64)
SERVERMOD_SUBDIR=$(SERVERMOD_SUBDIR.$(BITS))
X11_SERVERMODS_DIR=/usr/lib/xorg/modules

CPPFLAGS += -I/usr/include/xorg
CPPFLAGS += -I/usr/include/pixman-1

COMPONENT_COMMON_ENV = CC=$(CC)
COMPONENT_COMMON_ENV += CFLAGS="$(CFLAGS) --std=gnu99"
COMPONENT_COMMON_ENV += CPPFLAGS="$(CPPFLAGS)"
COMPONENT_COMMON_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_INSTALL_ARGS += MODULEDIR=$(X11_SERVERMODS_DIR)
COMPONENT_INSTALL_ARGS += ARCHLIBSUBDIR=$(SERVERMOD_SUBDIR)

COMPONENT_BUILD_ENV += $(COMPONENT_COMMON_ENV)
COMPONENT_INSTALL_ENV += INSTALL=$(INSTALL)

COMPONENT_POST_BUILD_ACTION = $(TOUCH) $(BUILD_DIR)

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

REQUIRED_PACKAGES += system/library
