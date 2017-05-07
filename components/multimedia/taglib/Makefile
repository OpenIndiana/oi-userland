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
# Copyright 2016 phorcys@126.com.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= taglib
COMPONENT_VERSION= 1.10
COMPONENT_FMRI = library/audio/taglib
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_PROJECT_URL = https://taglib.github.io/
COMPONENT_SUMMARY= taglib - a library for reading and editing the meta-data of several popular audio formats.
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:24c32d50042cb0ddf162eb263f8ac75c5a158e12bf32ed534c1d5c71ee369baa
COMPONENT_ARCHIVE_URL= \
  https://taglib.github.io/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE = LGPL

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/cmake.mk
include $(WS_TOP)/make-rules/ips.mk

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/gcc-4-runtime
REQUIRED_PACKAGES += system/library/math
