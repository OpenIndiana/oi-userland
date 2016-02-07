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

COMPONENT_NAME=           fslsfonts
COMPONENT_VERSION=        1.0.5
COMPONENT_FMRI=           x11/xfs/fslsfonts
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  the fslsfonts utility to list fonts from an xfs font server
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:f1ed55093356b78daec2678d22f52d42ec11fe88575562d734396962e626d7f6
COMPONENT_ARCHIVE_URL= \
  http://www.x.org/releases/individual/app/fslsfonts-1.0.5.tar.bz2
COMPONENT_PROJECT_URL = http://www.x.org/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= fslsfonts.license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)


REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libfs
