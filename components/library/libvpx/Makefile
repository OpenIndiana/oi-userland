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
# Copyright 2024 Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libvpx
COMPONENT_VERSION= 1.16.0
COMPONENT_SUMMARY= The WebM VP8/VP9 Codec SDK
COMPONENT_PROJECT_URL = https://www.webmproject.org/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:7a479a3c66b9f5d5542a4c6a1b7d3768a983b1e5c14c60a9396edc9b649e015c
COMPONENT_ARCHIVE_URL=	https://github.com/webmproject/libvpx/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI= library/video/libvpx
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE= BSD
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Required for 64-bit builds.
LDFLAGS += $(CC_BITS)

CONFIGURE_OPTIONS = --prefix=/usr
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --enable-vp8
CONFIGURE_OPTIONS += --enable-vp9
CONFIGURE_OPTIONS += --enable-postproc
CONFIGURE_OPTIONS += --enable-runtime-cpu-detect
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-examples
CONFIGURE_OPTIONS += --disable-static
ifeq ($(MACH), i386)
CONFIGURE_OPTIONS += --target=x86_64-solaris-gcc
endif
ifeq ($(MACH), sparc)
CONFIGURE_OPTIONS += --target=sparc-solaris-gcc
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
endif

COMPONENT_TEST_ARGS += -k -i
COMPONENT_TEST_TARGETS = test
# Ensure that test_libvpx is linked to libvpx.so from the proto area.
COMPONENT_TEST_ENV += LD_LIBRARY_PATH=$(PROTOUSRLIBDIR64)
COMPONENT_TEST_TRANSFORMS += \
	' -n ' \
	'-e "/PASSED/p" '

# Manually added build dependencies
REQUIRED_PACKAGES += developer/assembler/yasm
REQUIRED_PACKAGES += developer/documentation-tool/doxygen

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
