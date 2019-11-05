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
#
# Copyright (c) 2014 Nexenta Systems, Inc.  All rights reserved.

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= smartmontools
COMPONENT_SUMMARY= smartmontools contains utilities that control and monitor storage devices
COMPONENT_VERSION= 6.6
COMPONENT_FMRI= storage/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL= http://downloads.sourceforge.net/smartmontools
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:51f43d0fb064fccaf823bbe68cf0d317d0895ff895aa353b3339a3b316a53054
COMPONENT_ARCHIVE_URL= http://sourceforge.net/projects/smartmontools/files/smartmontools/${COMPONENT_VERSION}/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION =  ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --with-savestates
CONFIGURE_OPTIONS += --with-attributelog
CONFIGURE_OPTIONS += --with-drivedbdir=yes
CONFIGURE_OPTIONS += --with-smartdscriptdir=/usr/sbin
CONFIGURE_OPTIONS += --with-nvme-devicescan=yes

PKG_PROTO_DIRS += $(COMPONENT_DIR)/files

build:    $(BUILD_32)

test:     $(TEST_32)

install:  $(INSTALL_32)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
