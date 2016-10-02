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
# Copyright 2016 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           libfontenc
COMPONENT_VERSION=        1.1.3
COMPONENT_FMRI=           x11/library/libfontenc
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  libfontenc - font encoding table parser and mapping library
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:70588930e6fc9542ff38e0884778fbc6e6febf21adbab92fd8f524fe60aefd21
COMPONENT_ARCHIVE_URL= \
  http://www.x.org/releases/individual/lib/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.x.org/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= libfontenc.license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

X11_SERVERLIBS_DIR.32=/usr/lib/xorg
X11_SERVERLIBS_DIR.64=/usr/lib/xorg/$(MACH64)

CONFIGURE_DEFAULT_DIRS=no
CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --libdir=$(X11_SERVERLIBS_DIR.$(BITS))


build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)


REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
