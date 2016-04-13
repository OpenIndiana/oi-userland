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

COMPONENT_NAME= mkfontscale
COMPONENT_VERSION= 1.1.2
COMPONENT_SUMMARY= mkfontscale legacy X11 scalable font metadata creation tool
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:8c6d5228af885477b9aec60ca6f172578e7d2de42234357af62fb00439453f20
COMPONENT_ARCHIVE_URL= \
  http://ftp.x.org/pub/individual/app/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.x.org/wiki/
COMPONENT_FMRI= x11/mkfontscale
COMPONENT_LICENSE= MIT
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_CLASSIFICATION= System/X11

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS += --with-bzip2

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)
