#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.illumos.org/license/CDDL.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright 2017 Gary Mills
# Copyright (c) 2015, Predrag Zecevic. All rights reserved.
# Copyright (c) 2015, Aurelien Larcher. All rights reserved.
#
BUILD_STYLE=configure
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         protobuf
COMPONENT_VERSION=      3.5.1
COMPONENT_REVISION=     2
COMPONENT_FMRI=         library/c++/protobuf
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://github.com/google/protobuf/
COMPONENT_ARCHIVE=      v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:826425182ee43990731217b917c5c3ea7190cfda141af4869e6d4ad9085a740f
COMPONENT_ARCHIVE_URL=  https://github.com/google/protobuf/archive/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      BSD
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license 
COMPONENT_SUMMARY=      Protocol Buffers - Google data interchange format

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = cd $(SOURCE_DIR); ./autogen.sh

CONFIGURE_OPTIONS+=	--disable-static --disable-64bit-solaris

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
