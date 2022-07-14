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
#

BUILD_BITS=		64
BUILD_STYLE=	justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pystring
COMPONENT_VERSION=	1.1.3
COMPONENT_FMRI=		library/pystring
COMPONENT_PROJECT_URL=	https://github.com/imageworks/$(COMPONENT_NAME)
COMPONENT_SUMMARY=	C++ functions matching the interface and behavior of python string methods with std::string
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:358a56e756e701836b69a31c75d3d9d41c34d447cf7b3775bbd5620dcd3203d9
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk
PATH=$(PATH.gnu)

COMPONENT_TEST_TARGETS=test

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
