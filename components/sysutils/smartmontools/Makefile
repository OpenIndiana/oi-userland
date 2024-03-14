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
# Copyright 2016 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= smartmontools
COMPONENT_VERSION= 7.4
COMPONENT_SUMMARY= smartmontools contains utilities that control and monitor storage devices
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL= https://www.smartmontools.org/
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:e9a61f641ff96ca95319edfb17948cd297d0cd3342736b2c49c99d4716fb993d
COMPONENT_ARCHIVE_URL= https://sourceforge.net/projects/smartmontools/files/smartmontools/${COMPONENT_VERSION}/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= storage/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE= GPLv2

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION =  ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --with-savestates
CONFIGURE_OPTIONS += --with-attributelog
CONFIGURE_OPTIONS += --with-drivedbdir=yes
CONFIGURE_OPTIONS += --with-smartdscriptdir=$(USRSBINDIR)
CONFIGURE_OPTIONS += --sbindir=$(USRSBINDIR)
CONFIGURE_OPTIONS += --with-nvme-devicescan=yes
CONFIGURE_OPTIONS += --with-gnupg=/usr/bin/gpg2

PKG_PROTO_DIRS += $(COMPONENT_DIR)/files

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
