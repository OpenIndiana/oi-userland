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
# Copyright (c) 2020, Aurelien Larcher. All rights reserved.
# Copyright (c) 2023, Niklas Poslovski
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		spdlog
COMPONENT_VERSION=	1.17.0
COMPONENT_SUMMARY=      spdlog - Fast C++ logging library
COMPONENT_PROJECT_URL=	https://github.com/gabime/spdlog
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:d8862955c6d74e5846b3f580b1605d2428b11d97a410d86e2fb13e857cd3a744
COMPONENT_ARCHIVE_URL=	https://github.com/gabime/spdlog/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=     	library/c++/spdlog
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE=	LICENSE

COMPONENT_FMRI.library =	$(COMPONENT_FMRI)-$(subst .,,$(basename $(HUMAN_VERSION)))
COMPONENT_SUMMARY.library =	Runtime libraries for $(COMPONENT_NAME) $(basename $(HUMAN_VERSION))

# Tests now require Catch2 which we don't have yet.
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Do not create gpatch backup files because they pollute the generated manifest
GPATCH_BACKUP =

CMAKE_OPTIONS += -DSPDLOG_BUILD_SHARED=ON

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
