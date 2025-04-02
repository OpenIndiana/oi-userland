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

BUILD_STYLE= cmake
USE_PARALLEL_BUILD=yes
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         protobuf
COMPONENT_VERSION=      29.3
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=      Protocol Buffers - Google data interchange format
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://github.com/google/protobuf/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:008a11cc56f9b96679b4c285fd05f46d317d685be3ab524b2a310be0fbad987e
COMPONENT_ARCHIVE_URL=  https://github.com/google/protobuf/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=         library/c++/protobuf
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=		BSD-3-Clause
COMPONENT_LICENSE_FILE= LICENSE

COMPONENT_FMRI.library=		$(COMPONENT_FMRI)-$(subst .,,$(HUMAN_VERSION))
COMPONENT_SUMMARY.library=	$(COMPONENT_SUMMARY) (runtime libraries)

include $(WS_MAKE_RULES)/common.mk

# We need shared libraries, not static
CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON
# Make pkglint happy by avoiding $ORIGIN in rpath
CMAKE_OPTIONS += -DCMAKE_SKIP_INSTALL_RPATH=TRUE
# Use external (our packaged) googletest
CMAKE_OPTIONS += -Dprotobuf_USE_EXTERNAL_GTEST=ON
CMAKE_OPTIONS += -Dprotobuf_ABSL_PROVIDER=package

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/abseil-cpp
REQUIRED_PACKAGES += library/c++/abseil-cpp-2501
REQUIRED_PACKAGES += library/c++/protobuf
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
