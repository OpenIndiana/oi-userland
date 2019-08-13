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
# Copyright (c) 2008, 2019, Oracle and/or its affiliates. All rights reserved.
#

FONT_TYPE=X11
BUILD_STYLE=configure
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		font-misc-cyrillic
COMPONENT_VERSION= 	1.0.3
COMPONENT_ARCHIVE_HASH=	\
	sha256:e40fe3e3323c62b738550795457ad555c70c008aa91b5912dfd46f8e745f5e60

COMPONENT_NAME_1=	font-cronyx-cyrillic
COMPONENT_VERSION_1= 	1.0.3
COMPONENT_ARCHIVE_HASH_1=	\
	sha256:6e8631936157677c77ba032b5c7b1fb3cb2ee872dbcea0444f12cd602cd9212a

COMPONENT_NAME_2=	font-screen-cyrillic
COMPONENT_VERSION_2= 	1.0.4
COMPONENT_ARCHIVE_HASH_2=	\
	sha256:824231e8dffe15299454e47259f29d98001c9cf8ad3d6b5171399e4d71705e79

COMPONENT_NAME_3=	font-winitzki-cyrillic
COMPONENT_VERSION_3= 	1.0.3
COMPONENT_ARCHIVE_HASH_3=	\
	sha256:abd13b63d02fcaec488686c23683e5cf640b43bd32f8ca22eeae6f84df0a36a0

# Use font-screen-cyrillic version number as solaris-userland does
IPS_COMPONENT_VERSION=$(COMPONENT_VERSION_2)

LIST = 1 2 3

BUILD_TARGET = $(BUILD_$(MK_BITS))
INSTALL_TARGET = $(INSTALL_$(MK_BITS))

define extra-target-rules
$(BUILD_DIR)/%_$(1)/.configured: SOURCE_DIR=$$(SOURCE_DIR_$(1))
endef

$(foreach n, $(LIST), \
    $(eval COMPONENT_SRC_$(n) = $(COMPONENT_NAME_$(n))-$(COMPONENT_VERSION_$(n))) \
    $(eval COMPONENT_ARCHIVE_$(n) = $(COMPONENT_SRC_$(n)).tar.bz2) \
    $(eval COMPONENT_ARCHIVE_URL_$(n) = $$(COMPONENT_ARCHIVE_URL:$$(COMPONENT_ARCHIVE)=$(COMPONENT_ARCHIVE_$(n)))) \
    $(eval BUILD_DIR_$(n) += $(BUILD_DIR_NO_ARCH)_$(n)) \
    $(eval CONFIGURE_NO_ARCH += $(BUILD_DIR_$(n))/.configured) \
    $(eval BUILD_NO_ARCH_$(n) += $(BUILD_DIR_$(n))/.built) \
    $(eval BUILD_TARGET += $(BUILD_NO_ARCH_$(n))) \
    $(eval INSTALL_NO_ARCH_$(n) += $(BUILD_DIR_$(n))/.installed) \
    $(eval INSTALL_TARGET += $(INSTALL_NO_ARCH_$(n))) \
    $(eval $(call extra-target-rules,$(n))) \
)

include $(WS_MAKE_RULES)/x11.mk
include $(WS_MAKE_RULES)/font.mk

CYRILLIC_FONT_DIR = $(USRSHAREX11FONTSDIR)/cyrillic

# Install to separate directory for easier packaging
CONFIGURE_OPTIONS += --with-fontdir=$(CYRILLIC_FONT_DIR)

include $(WS_MAKE_RULES)/common.mk
