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
COMPONENT_VERSION= 1.11.1
COMPONENT_FMRI = library/audio/taglib
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_PROJECT_URL = https://taglib.github.io/
COMPONENT_SUMMARY= taglib - a library for reading and editing the meta-data of several popular audio formats.
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:b6d1a5a610aae6ff39d93de5efd0fdc787aa9e9dc1e7026fa4c961b26563526b
COMPONENT_ARCHIVE_URL= \
  https://taglib.github.io/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE = LGPL

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
