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

COMPONENT_NAME= libyajl2
COMPONENT_VERSION= 2.1.0
COMPONENT_FMRI = library/libyajl2
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_SUMMARY= YAJL is a small event-driven (SAX-style) JSON parser written in ANSI C, and a small validating JSON generator.
COMPONENT_SRC= yajl-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:3fb73364a5a30efe615046d07e6db9d09fd2b41c763c5f7d3bfb121cd5c5ac5a
COMPONENT_ARCHIVE_URL= \
  https://github.com/lloyd/yajl/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL = https://lloyd.github.io/yajl/
COMPONENT_LICENSE = ISC

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CMAKE_OPTIONS += -DSTATIC_BUILD=NO
CMAKE_OPTIONS += -DLIB_SUFFIX=/$(ARCHLIBSUBDIR)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += system/library
