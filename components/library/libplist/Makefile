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

COMPONENT_NAME= libplist
COMPONENT_VERSION= 1.12
COMPONENT_FMRI = library/libplist
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_PROJECT_URL = https://github.com/libimobiledevice/libplist
COMPONENT_SUMMARY= A library to handle Apple Property List format in binary or XML
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:b8e860ef2e01154e79242438252b2a7ed185df351f02c167147a8a602a0aa63e
COMPONENT_ARCHIVE_URL= \
  https://github.com/libimobiledevice/libplist/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE = GPLv2,LGPLv2.1

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk


COMPONENT_PREP_ACTION= \
    ( cd  $(@D) && NOCONFIGURE=true sh autogen.sh )

CFLAGS += $($(COMPILER)_PIC)

CONFIGURE_OPTIONS+= --disable-static

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
