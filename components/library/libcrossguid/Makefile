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

COMPONENT_NAME= libcrossguid
COMPONENT_VERSION= 1.0.0
COMPONENT_FMRI = library/libcrossguid
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_PROJECT_URL = https://github.com/graeme-hill/crossguid/
COMPONENT_SUMMARY= CrossGuid is a minimal, cross platform, C++ GUID library.
COMPONENT_SRC_NAME= crossguid
COMPONENT_SRC_VERSION= 8f399e8bd4
COMPONENT_SRC= $(COMPONENT_SRC_NAME)-$(COMPONENT_SRC_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:3d77d09a5df0de510aeeb940df4cb534787ddff3bb1828779753f5dfa1229d10
COMPONENT_ARCHIVE_URL= \
  http://ftp.heanet.ie/mirrors/xbmc/build-deps/sources/$(COMPONENT_SRC).tar.gz
COMPONENT_LICENSE = MIT

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CFLAGS+= -DGUID_LIBUUID

COMPONENT_PREP_ACTION= \
    ( cd  $(@D) && \
      touch NEWS README AUTHORS ChangeLog && \
		  libtoolize && aclocal && autoconf && automake --add-missing )

COMPONENT_POST_INSTALL_ACTION= \
    ( $(GSED) -e "s:%LIBDIR%:$(CONFIGURE_LIBDIR.$(BITS)):g" \
              -e "s:%VERSION%:$(COMPONENT_VERSION):g" \
              $(SOURCE_DIR)/crossguid.pc > $(BUILD_DIR)/crossguid.pc.$(BITS)  )

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
