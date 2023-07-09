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
# Copyright 2023 Andreas Wacknitz
#
BUILD_BITS= 64_and_32
USE_COMMON_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libvpx
COMPONENT_VERSION= 1.13.0
COMPONENT_SUMMARY= The WebM VP8/VP9 Codec SDK
COMPONENT_PROJECT_URL = http://www.webmproject.org/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:cb2a393c9c1fae7aba76b950bb0ad393ba105409fe1a147ccd61b0aaa1501066
COMPONENT_ARCHIVE_URL=	https://github.com/webmproject/libvpx/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI = library/video/libvpx
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_LICENSE = BSD
COMPONENT_LICENSE_FILE = LICENSE

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Required for 64-bit builds.
LDFLAGS += $(CC_BITS)

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
# Ensure that test_libvpx is linked to libvpx.so from the proto area.
TEST_LIBPATH.32 =   $(PROTOUSRLIBDIR)
TEST_LIBPATH.64 =   $(PROTOUSRLIBDIR64)
COMPONENT_TEST_ENV +=   LD_LIBRARY_PATH=$(TEST_LIBPATH.$(BITS))
COMPONENT_TEST_TRANSFORMS += \
        '-e "s/ ([0-9]\+ ms.*)//" ' \
        '-n ' \
        '-e "/tests/p" ' \
        '-e "/RUN/p" ' \
        '-e "/OK/p" '

# Manually added build dependencies
REQUIRED_PACKAGES += developer/assembler/yasm
REQUIRED_PACKAGES += developer/documentation-tool/doxygen

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
