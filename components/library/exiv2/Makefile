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
# Copyright 2017 Carsten Grzemba
#

BUILD_BITS= 64_and_32
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= exiv2
COMPONENT_VERSION= 0.27.3
COMPONENT_SUMMARY= Image metadata library and tools
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)-Source
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:a79f5613812aa21755d578a297874fb59a85101e793edc64ec2c6bd994e3e778
COMPONENT_ARCHIVE_URL= \
  http://www.exiv2.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.exiv2.org
COMPONENT_FMRI = image/library/exiv2
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_CLASSIFICATION = System/Multimedia Libraries

TEST_TARGET=$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# mkdir option '-v' is used
PATH=$(PATH.gnu)

LDFLAGS += -lnsl -lsocket

REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
