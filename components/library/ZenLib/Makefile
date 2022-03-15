#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022, Daniel Chan
#

BUILD_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ZenLib
COMPONENT_VERSION=	0.4.39
COMPONENT_SUMMARY=	Small C++ derivate classes to have an easier life
COMPONENT_PROJECT_URL=	https://github.com/MediaArea/ZenLib
COMPONENT_FMRI=		library/libzen
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/MediaArea/$(COMPONENT_NAME)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:a29fcafe41afac4ff818414ada18e4549bb2e77b2962bba2dd39db5cf747044e
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE= License.txt

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_SCRIPT =	$(SOURCE_DIR)/Project/GNU/Library/configure
COMPONENT_PRE_CONFIGURE_ACTION=	( cd $(SOURCE_DIR)/Project/GNU/Library/ && ./autogen.sh && cd $(SOURCE_DIR); )

CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static
COMPONENT_POST_UNPACK_ACTION= \
			mv ZenLib-0.4.39/Source/ZenLib/Thread.cpp ZenLib-0.4.39/Source/ZenLib/Thread.cpp.old; \
			dos2unix ZenLib-0.4.39/Source/ZenLib/Thread.cpp.old &> ZenLib-0.4.39/Source/ZenLib/Thread.cpp

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
