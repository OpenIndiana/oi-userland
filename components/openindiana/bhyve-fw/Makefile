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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		uefi-edk2
COMPONENT_VERSION=	20210201
COMPONENT_REVISION=	2
COMPONENT_FMRI=		system/bhyve/firmware
COMPONENT_CLASSIFICATION=System/Core
COMPONENT_SUMMARY=	UEFI-EDK2(+CSM) firmware for bhyve

COMPONENT_TAG=		il-udk2014.sp1-3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_TAG)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_TAG).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:998236765edaa683afc9a4799d40992c92d7ed543abf3fd28a3bc8b40aa2bc3d
COMPONENT_ARCHIVE_URL= \
	https://github.com/illumos/$(COMPONENT_NAME)/releases/download/$(COMPONENT_TAG)/$(COMPONENT_ARCHIVE)

COMPONENT_TAG_1=	il-edk2-stable202102-1
COMPONENT_SRC_1=	$(COMPONENT_NAME)-$(COMPONENT_TAG_1)
COMPONENT_ARCHIVE_1=	$(COMPONENT_NAME)-$(COMPONENT_TAG_1).tar.xz
COMPONENT_ARCHIVE_HASH_1= \
	sha256:ca26699ec8f8f7e45e01f2d5a23649997d33f0b8437405ca731f6e301d6a71a8
COMPONENT_ARCHIVE_URL_1= \
	https://github.com/illumos/$(COMPONENT_NAME)/releases/download/$(COMPONENT_TAG_1)/$(COMPONENT_ARCHIVE_1)

COMPONENT_PROJECT_URL=	https://github.com/illumos/uefi-edk2
COMPONENT_LICENSE=	simplified-BSD

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

ENV = /usr/bin/env -i

COMPONENT_BUILD_ENV = PATH=$(PATH.illumos)
COMPONENT_BUILD_ENV += GMAKE=/usr/bin/gmake
COMPONENT_BUILD_ENV += GAS=/usr/bin/gas
COMPONENT_BUILD_ENV += GAR=/usr/bin/gar
COMPONENT_BUILD_ENV += GLD=/usr/bin/gld
COMPONENT_BUILD_ENV += GOBJCOPY=/usr/bin/gobjcopy

# Four variants of the bhyve firmware are built;
# DEBUG and RELEASE, and with and without CSM.
VARIANTS =	DEBUG DEBUG.csm RELEASE RELEASE.csm

BUILD_64 =	$(VARIANTS:%=$(BUILD_DIR)/%/.built)
INSTALL_64 =	$(VARIANTS:%=$(BUILD_DIR)/%/.installed)

COMPONENT_BUILD_ACTION = \
	cd $(@D); $(ENV) $(COMPONENT_BUILD_ENV) \
	./build $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS)

$(BUILD_DIR)/RELEASE/.built: SOURCE_DIR = $(SOURCE_DIR_1)
$(BUILD_DIR)/RELEASE/.built: COMPONENT_BUILD_ENV += GCCPATH=$(GCC_ROOT)
$(BUILD_DIR)/RELEASE/.built: COMPONENT_BUILD_ARGS =
$(BUILD_DIR)/RELEASE/.built: COMPONENT_BUILD_TARGETS = RELEASE

$(BUILD_DIR)/DEBUG/.built: SOURCE_DIR = $(SOURCE_DIR_1)
$(BUILD_DIR)/DEBUG/.built: COMPONENT_BUILD_ENV += GCCPATH=$(GCC_ROOT)
$(BUILD_DIR)/DEBUG/.built: COMPONENT_BUILD_ARGS =
$(BUILD_DIR)/DEBUG/.built: COMPONENT_BUILD_TARGETS = DEBUG

$(BUILD_DIR)/RELEASE.csm/.built: COMPONENT_BUILD_ENV += GCCPATH=/opt/gcc/4.4.4
$(BUILD_DIR)/RELEASE.csm/.built: COMPONENT_BUILD_ARGS = -csm
$(BUILD_DIR)/RELEASE.csm/.built: COMPONENT_BUILD_TARGETS = RELEASE

$(BUILD_DIR)/DEBUG.csm/.built: COMPONENT_BUILD_ENV += GCCPATH=/opt/gcc/4.4.4
$(BUILD_DIR)/DEBUG.csm/.built: COMPONENT_BUILD_ARGS = -csm
$(BUILD_DIR)/DEBUG.csm/.built: COMPONENT_BUILD_TARGETS = DEBUG

COMPONENT_PRE_INSTALL_ACTION = \
	$(MKDIR) -p $(PROTO_DIR)/usr/share/bhyve/firmware

COMPONENT_INSTALL_ACTION = \
	cd $(@D); \
	$(CP) ./Build/BhyveX64/$(COMPONENT_INSTALL_TARGETS)_ILLGCC/FV/$(COMPONENT_INSTALL_SOURCE) \
	    $(PROTO_DIR)/usr/share/bhyve/firmware/$(COMPONENT_INSTALL_FILE)

$(BUILD_DIR)/DEBUG/.installed: COMPONENT_INSTALL_SOURCE = BHYVE_CODE.fd
$(BUILD_DIR)/DEBUG/.installed: COMPONENT_INSTALL_TARGETS = DEBUG
$(BUILD_DIR)/DEBUG/.installed: COMPONENT_INSTALL_FILE = BHYVE_DEBUG.fd

$(BUILD_DIR)/DEBUG.csm/.installed: COMPONENT_INSTALL_SOURCE = BHYVE.fd
$(BUILD_DIR)/DEBUG.csm/.installed: COMPONENT_INSTALL_TARGETS = DEBUG
$(BUILD_DIR)/DEBUG.csm/.installed: COMPONENT_INSTALL_FILE = BHYVE_DEBUG_CSM.fd

$(BUILD_DIR)/RELEASE/.installed: COMPONENT_INSTALL_SOURCE = BHYVE_CODE.fd
$(BUILD_DIR)/RELEASE/.installed: COMPONENT_INSTALL_TARGETS = RELEASE
$(BUILD_DIR)/RELEASE/.installed: COMPONENT_INSTALL_FILE = BHYVE_RELEASE.fd
$(BUILD_DIR)/RELEASE/.installed: \
	COMPONENT_POST_INSTALL_ACTION = \
	    $(LN) -s $(COMPONENT_INSTALL_FILE) \
		$(PROTO_DIR)/usr/share/bhyve/firmware/BHYVE.fd; \
	    $(CP) $(@D)/Build/BhyveX64/$(COMPONENT_INSTALL_TARGETS)_ILLGCC/FV/BHYVE_VARS.fd \
		$(PROTO_DIR)/usr/share/bhyve/firmware/BHYVE_VARS.fd

$(BUILD_DIR)/RELEASE.csm/.installed: COMPONENT_INSTALL_SOURCE = BHYVE.fd
$(BUILD_DIR)/RELEASE.csm/.installed: COMPONENT_INSTALL_TARGETS = RELEASE
$(BUILD_DIR)/RELEASE.csm/.installed: COMPONENT_INSTALL_FILE = BHYVE_RELEASE_CSM.fd
$(BUILD_DIR)/RELEASE.csm/.installed: \
	COMPONENT_POST_INSTALL_ACTION = $(LN) -s $(COMPONENT_INSTALL_FILE) \
	$(PROTO_DIR)/usr/share/bhyve/firmware/BHYVE_CSM.fd

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += developer/acpi
REQUIRED_PACKAGES += developer/illumos-gcc

# Auto-generated dependencies
