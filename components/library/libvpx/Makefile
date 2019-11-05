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
PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libvpx
COMPONENT_VERSION= 1.7.0
COMPONENT_SUMMARY= The WebM VP8/VP9 Codec SDK
COMPONENT_PROJECT_URL = http://www.webmproject.org/
COMPONENT_FMRI = library/video/libvpx
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:1fec931eb5c94279ad219a5b6e0202358e94a93a90cfb1603578c326abfc1238
COMPONENT_ARCHIVE_URL= \
  https://github.com/webmproject/libvpx/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE = BSD
COMPONENT_LICENSE_FILE = LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

TARGET.32 = x86-solaris-gcc
TARGET.64 = x86_64-solaris-gcc

CONFIGURE_OPTIONS = --prefix=/usr
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --enable-vp8
CONFIGURE_OPTIONS += --enable-vp9
CONFIGURE_OPTIONS += --enable-postproc
CONFIGURE_OPTIONS += --enable-runtime-cpu-detect
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-examples
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --target=$(TARGET.$(BITS))

unexport SHELLOPTS
COMPONENT_TEST_ARGS += -k -i
COMPONENT_TEST_TARGETS = test
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/PASSED/p" ' \
        '-e "/tests/p" ' \
        '-e "/RUN/p" ' \
        '-e "/OK/p" ' \
        '-e "/ERROR/p" '
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
