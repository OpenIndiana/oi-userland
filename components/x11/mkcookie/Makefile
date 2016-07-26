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

COMPONENT_NAME= mkcookie
COMPONENT_VERSION= 0.5.11
COMPONENT_SUMMARY= utility used to generate fresh 'Magic Cookies'
COMPONENT_SRC= src
COMPONENT_PROJECT_URL = https://hg.java.net/hg/solaris-x11~x-s12-clone
COMPONENT_FMRI= x11/session/mkcookie
COMPONENT_LICENSE= MIT
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_CLASSIFICATION= System/X11

include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

LDFLAGS += -L/usr/lib/xorg -R/usr/lib/xorg

COMPONENT_COMMON_ENV = CC=$(CC)
COMPONENT_COMMON_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_COMMON_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_BUILD_ENV += $(COMPONENT_COMMON_ENV)
COMPONENT_INSTALL_ENV += INSTALL=$(INSTALL)
COMPONENT_INSTALL_ENV += PREFIX=/usr

download:

$(SOURCE_DIR)/.prep:
	$(TOUCH) $@

clobber: clean

clean::
	$(RM) $(SOURCE_DIR)/.prep

$(BUILD_32):	Makefile

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libxau
