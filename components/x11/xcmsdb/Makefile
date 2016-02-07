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

COMPONENT_NAME=           xcmsdb
COMPONENT_VERSION=        1.0.5
COMPONENT_FMRI=           x11/xcmsdb
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  the xcmsdb Device Color Characterization utility
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:e5585361bb8b6a05bb814a8d0e444ee93e0f00180881d3070aff4571e97f67c6
COMPONENT_ARCHIVE_URL= \
  http://www.x.org/releases/individual/app/xcmsdb-1.0.5.tar.bz2
COMPONENT_PROJECT_URL = http://www.x.org/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= xcmsdb.license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)


REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
