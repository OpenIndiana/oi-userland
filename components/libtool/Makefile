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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
# libtool only delivers scripts that embed paths, so prefer 32-bit.
BUILD_BITS= 32_and_64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libtool
COMPONENT_VERSION=	2.4.2
COMPONENT_ARCHIVE_HASH=	\
    sha256:b38de44862a987293cd3d8dfae1c409d514b6c4e794ebc93648febf9afc38918
COMPONENT_BUGDB=	utility/libtool

TPNO=			9088

# For now, we want to continue to provide the libltdl.so's (and their
# links) from libtool 1.5.22.
#
COMPONENT_VERSION_1 =	1.5.22
COMPONENT_SRC_1 =	$(COMPONENT_NAME)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1 =	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1 = \
    sha256:88e9ffaaade21c1ddaf6297723dd2fb4ca18ccaef0499a28b6e672f02c8ceb5d
COMPONENT_ARCHIVE_URL_1 = http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE_1)
SOURCE_DIR_1 =		$(COMPONENT_DIR)/$(COMPONENT_SRC_1)

BUILD_TARGET=
INSTALL_TARGET=
include $(WS_MAKE_RULES)/gnu-component.mk

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		PERL="$(PERL)"

# requires an older automake to reconfigure.
COMPONENT_PREP_ACTION = \
	(cd $(@D) ; ACLOCAL=aclocal-1.11 AUTOMAKE=automake-1.11 ./bootstrap)

# Remove the hard-wired compiler locations in the LTCC and two CC lines
# in the two versions of the libtool script.
COMPONENT_POST_INSTALL_ACTION = \
	cd $(PROTO_DIR)$(USRBIN.$(BITS)); \
	$(GSED) -i \
		-e 's|^LTCC="/.*$$|LTCC="cc"|' \
		-e 's|^CC="/.*$$|CC="cc"|' libtool ; \

# Macros to configure, build, and install the old version for the time being.
BUILD_OLD_DIR_32 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH32)
BUILD_OLD_DIR_64 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH64)

$(BUILD_OLD_DIR_32)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_1)/configure
$(BUILD_OLD_DIR_64)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_1)/configure
$(BUILD_OLD_DIR_32)/.configured:	BITS=32
$(BUILD_OLD_DIR_64)/.configured:	BITS=64

BUILD_32 += $(BUILD_OLD_DIR_32)/.built
BUILD_64 += $(BUILD_OLD_DIR_64)/.built

INSTALL_32 += $(BUILD_OLD_DIR_32)/.installed
INSTALL_64 += $(BUILD_OLD_DIR_64)/.installed

# install the old version first
$(BUILD_DIR_32)/.installed:	$(BUILD_OLD_DIR_32)/.installed
$(BUILD_DIR_64)/.installed:	$(BUILD_OLD_DIR_64)/.installed

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/^===/p" ' \
	'-e "/failed/p" ' \
	'-e "/passed/p" '

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

REQUIRED_PACKAGES += developer/base-developer-utilities
REQUIRED_PACKAGES += developer/gnu-binutils
REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += text/gnu-grep
REQUIRED_PACKAGES += text/gnu-sed
