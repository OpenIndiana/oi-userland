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
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE = cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         protobuf
COMPONENT_VERSION=      24.4
COMPONENT_FMRI=         library/c++/protobuf
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://github.com/google/protobuf/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:616bb3536ac1fff3fb1a141450fa28b875e985712170ea7f1bfe5e5fc41e2cd8
COMPONENT_ARCHIVE_URL=  https://github.com/google/protobuf/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=      BSD
COMPONENT_LICENSE_FILE= LICENSE
COMPONENT_SUMMARY=      Protocol Buffers - Google data interchange format

# Tests require Googletest which we don't have yet.
TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -Dprotobuf_BUILD_TESTS=OFF
CMAKE_OPTIONS += -Dprotobuf_BUILD_SHARED_LIBS=ON
CMAKE_OPTIONS += -Dprotobuf_ABSL_PROVIDER=package

#COMPONENT_POST_INSTALL_ACTION = \
#    /usr/bin/elfedit -e 'dyn:delete RUNPATH' $(PROTO_DIR)/usr/bin/protoc; \
#    /usr/bin/elfedit -e 'dyn:delete RPATH' $(PROTO_DIR)/usr/bin/protoc;

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/abseil-cpp
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
