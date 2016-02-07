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

COMPONENT_NAME=           xscope
COMPONENT_VERSION=        1.4.1
COMPONENT_FMRI=           x11/diagnostic/xscope
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  xscope - X Window Protocol Viewer
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:33807fbd51822435b23c28e7e78116e552826a6ca4d85632f098ad0ddf1ff423
COMPONENT_ARCHIVE_URL= \
  http://www.x.org/releases/individual/app/xscope-1.4.1.tar.bz2
COMPONENT_PROJECT_URL = http://www.x.org/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= xscope.license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CPPFLAGS+= -DFD_SETSIZE=256

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)


REQUIRED_PACKAGES += system/library
