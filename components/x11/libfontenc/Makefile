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
# Copyright 2015 Captain XNV
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           libfontenc
COMPONENT_VERSION=        1.1.2
COMPONENT_FMRI=           x11/library/libfontenc
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  libfontenc - font encoding table parser and mapping library
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:a9a4efed3359b2e80161bb66b65038fac145137fa134e71335264cbc23b02f62
COMPONENT_ARCHIVE_URL= \
  http://www.x.org/releases/individual/lib/libfontenc-1.1.2.tar.bz2
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
