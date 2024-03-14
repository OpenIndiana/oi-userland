#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022 Daniel Chan
# Copyright 2023 Andreas Wacknitz
#

BUILD_BITS= 64
BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pystring
COMPONENT_VERSION=	1.1.4
COMPONENT_SUMMARY=	C++ functions matching the interface and behavior of python string methods with std::string
COMPONENT_PROJECT_URL=	https://github.com/imageworks/$(COMPONENT_NAME)
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:49da0fe2a049340d3c45cce530df63a2278af936003642330287b68cefd788fb
COMPONENT_FMRI=				library/pystring
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=		MIT
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk
PATH= $(PATH.gnu)

COMPONENT_TEST_TARGETS= test
COMPONENT_TEST_TRANSFORMS += \
	' -n ' \
	' -e "/PASSED/p" ' \
	' -e "/FAILED/p" ' \
	' -e "/failed/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
