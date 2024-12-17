#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022 OmniOS Community Edition (OmniOSce) Association.
#

BUILD_STYLE = justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		uefi-edk2
COMPONENT_VERSION=	20230801
COMPONENT_REVISION=	1
COMPONENT_FMRI=		system/bhyve/firmware
COMPONENT_CLASSIFICATION=System/Core
COMPONENT_SUMMARY=	UEFI-EDK2 firmware for bhyve

COMPONENT_TAG=		il-edk2-stable202308-1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_TAG)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_TAG).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:8aaacf4b7c6a875c78492ad74856802abcbce89ee8cf980efbd12c74946b3b79
COMPONENT_ARCHIVE_URL= \
	https://github.com/illumos/$(COMPONENT_NAME)/releases/download/$(COMPONENT_TAG)/$(COMPONENT_ARCHIVE)

COMPONENT_PROJECT_URL=	https://github.com/illumos/uefi-edk2
COMPONENT_LICENSE=	simplified-BSD

TEST_TARGET = $(NO_TESTS)

# Two variants of the bhyve firmware are built;
# DEBUG and RELEASE
VARIANTS =	DEBUG RELEASE

# Custom BUILD_*, and INSTALL_*, variables needs to be defined before the
# common.mk include.
BUILD_64 =	$(VARIANTS:%=$(BUILD_DIR)/%/.built)
INSTALL_64 =	$(VARIANTS:%=$(BUILD_DIR)/%/.installed)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ENV = PATH=$(PATH.illumos)
COMPONENT_BUILD_ENV += GMAKE=/usr/bin/gmake
COMPONENT_BUILD_ENV += GAS=/usr/bin/gas
COMPONENT_BUILD_ENV += GAR=/usr/bin/gar
COMPONENT_BUILD_ENV += GLD=/usr/bin/gld
COMPONENT_BUILD_ENV += GOBJCOPY=/usr/bin/gobjcopy

COMPONENT_BUILD_ACTION = \
	cd $(@D); $(ENV) $(COMPONENT_BUILD_ENV) \
	./build $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS)

$(BUILD_DIR)/RELEASE/.built: COMPONENT_BUILD_ENV += GCCPATH=$(GCC_ROOT)
$(BUILD_DIR)/RELEASE/.built: COMPONENT_BUILD_ARGS =
$(BUILD_DIR)/RELEASE/.built: COMPONENT_BUILD_TARGETS = RELEASE

$(BUILD_DIR)/DEBUG/.built: COMPONENT_BUILD_ENV += GCCPATH=$(GCC_ROOT)
$(BUILD_DIR)/DEBUG/.built: COMPONENT_BUILD_ARGS =
$(BUILD_DIR)/DEBUG/.built: COMPONENT_BUILD_TARGETS = DEBUG

COMPONENT_PRE_INSTALL_ACTION = \
	$(MKDIR) $(PROTO_DIR)/usr/share/bhyve/firmware

COMPONENT_INSTALL_ACTION = \
	cd $(@D); \
	$(CP) ./Build/BhyveX64/$(COMPONENT_INSTALL_TARGETS)_ILLGCC/FV/$(COMPONENT_INSTALL_SOURCE) \
	    $(PROTO_DIR)/usr/share/bhyve/firmware/$(COMPONENT_INSTALL_FILE)

$(BUILD_DIR)/DEBUG/.installed: COMPONENT_INSTALL_SOURCE = BHYVE_CODE.fd
$(BUILD_DIR)/DEBUG/.installed: COMPONENT_INSTALL_TARGETS = DEBUG
$(BUILD_DIR)/DEBUG/.installed: COMPONENT_INSTALL_FILE = BHYVE_DEBUG.fd

$(BUILD_DIR)/RELEASE/.installed: COMPONENT_INSTALL_SOURCE = BHYVE_CODE.fd
$(BUILD_DIR)/RELEASE/.installed: COMPONENT_INSTALL_TARGETS = RELEASE
$(BUILD_DIR)/RELEASE/.installed: COMPONENT_INSTALL_FILE = BHYVE_RELEASE.fd
$(BUILD_DIR)/RELEASE/.installed: \
	COMPONENT_POST_INSTALL_ACTION = \
	    $(LN) -s $(COMPONENT_INSTALL_FILE) \
		$(PROTO_DIR)/usr/share/bhyve/firmware/BHYVE.fd; \
	    $(CP) $(@D)/Build/BhyveX64/$(COMPONENT_INSTALL_TARGETS)_ILLGCC/FV/BHYVE_VARS.fd \
		$(PROTO_DIR)/usr/share/bhyve/firmware/BHYVE_VARS.fd

# Build dependencies
REQUIRED_PACKAGES += developer/acpi

# Auto-generated dependencies
