#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2020, 2021, Andreas Wacknitz
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			doxygen
COMPONENT_VERSION=		1.9.7
COMPONENT_VERSION_=		$(subst .,_,$(COMPONENT_VERSION))
COMPONENT_SUMMARY=		Doxygen - Source Code Documentation Tool 
COMPONENT_PROJECT_URL=	https://www.doxygen.nl
COMPONENT_FILE=			Release_$(COMPONENT_VERSION_)
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_FILE)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).src.tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:691777992a7240ed1f822a5c2ff2c4273b57c1cf9fc143553d87f91a0c5970ee
COMPONENT_ARCHIVE_URL=	https://github.com/doxygen/doxygen/archive/$(COMPONENT_FILE).tar.gz
COMPONENT_FMRI=			developer/documentation-tool/doxygen		
COMPONENT_CLASSIFICATION= Development/Distribution Tools
COMPONENT_LICENSE=		GPLv2
COMPONENT_LICENSE_FILE=	LICENSE

# Download the manual so that we don't have to keep updating it in the gate.
COMPONENT_ARCHIVE_1=	$(COMPONENT_NAME)_manual-$(COMPONENT_VERSION).pdf.zip
COMPONENT_ARCHIVE_HASH_1=	sha256:c1fb74ce88be09a7ecaa4662ca45c0b96776d58813ddbda577400f0bb0fe7728
COMPONENT_ARCHIVE_URL_1=	https://doxygen.nl/files/$(COMPONENT_ARCHIVE_1)

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION= ($(CLONEY) $(SOURCE_DIR) $(@D))

CMAKE_OPTIONS += -G "Unix Makefiles"
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release

ASLR_MODE= $(ASLR_ENABLE)

# Test 12 is a known failure (we don't have bibtex in Solaris).
COMPONENT_TEST_ENV=		PATH="$(PROTO_DIR)/usr/bin:$(PATH)"
COMPONENT_TEST_DIR=		$(BUILD_DIR_64)/testing
COMPONENT_TEST_TARGETS=	tests

# The additional doxygen specific set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
	'-e "s/[0-9. ]*sec//g"' \
	'-e "/Passed/d" ' \
	'-e "/Total/d" ' \
	'-e "/Start/d" ' 

# common targets
install:	$(INSTALL_64)
	$(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1) 
	[ -f $(PROTO_DIR)/doxygen_manual-$(IPS_COMPONENT_VERSION).pdf ] || \
	  $(MV) doxygen_manual-$(IPS_COMPONENT_VERSION).pdf $(PROTO_DIR)
	$(INSTALL) -d $(PROTOUSRSHAREMAN1DIR)
	$(INSTALL) -vm644 $(SOURCE_DIR)/doc/*.1 $(PROTOUSRSHAREMAN1DIR)

# Build dependencies
REQUIRED_PACKAGES+= developer/lexer/flex

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
