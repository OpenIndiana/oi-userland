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

COMPONENT_NAME=           xorg-cf-files
COMPONENT_VERSION=        1.0.6
COMPONENT_FMRI=           developer/build/imake/xorg-cf-files
COMPONENT_CLASSIFICATION= Development/X11
COMPONENT_SUMMARY=  X.Org platform configuration files for imake
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:4dcf5a9dbe3c6ecb9d2dd05e629b3d373eae9ba12d13942df87107fdc1b3934d
COMPONENT_ARCHIVE_URL= \
  https://www.x.org/releases/individual/util/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.x.org/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= xorg-cf-files.license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

