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
#

BUILD_BITS= 64
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ixion
COMPONENT_VERSION=	0.18.1
COMPONENT_SUMMARY=      ixion - General purpose formula parser and interpreter
COMPONENT_PROJECT_URL=	https://gitlab.com/ixion/ixion
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:6969e5bd475da5397b5e007d55749e5d0f0a502a72ac6f9a0bb40bbcabebc6e8
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/-/archive/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=     	library/c++/libixion
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      MPLv2
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

# Note that this package depends on mdds version.
CMAKE_OPTIONS += -DMDDS_INCLUDEDIR=$(USRINCDIR)/mdds-2.1

COMPONENT_TEST_ENV += LD_LIBRARY_PATH=$(BUILD_DIR_$(BITS))/src

COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9. ]*sec//g"'

# Build dependencies
REQUIRED_PACKAGES+= library/c++/mdds
REQUIRED_PACKAGES+= library/c++/spdlog

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/boost
REQUIRED_PACKAGES += system/library/math
