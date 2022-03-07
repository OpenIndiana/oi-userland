#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2013 - 2016 Adam Stevko. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pciutils
COMPONENT_VERSION=	3.7.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH =	sha256:08c27e01030d1fcc700d02bc2ea66c638f58a3d150e45e58852aa82ad4160d84
COMPONENT_ARCHIVE_URL =		https://mj.ucw.cz/download/linux/pci/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL =		https://mj.ucw.cz/sw/pciutils/
COMPONENT_FMRI=		system/pciutils
COMPONENT_CLASSIFICATION =	System/Hardware
COMPONENT_SUMMARY=	The PCI Utilities are a collection of programs for inspecting and manipulating configuration of PCI devices
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

BUILD_STYLE =	justmake

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ARGS += CC=$(CC)
COMPONENT_BUILD_ARGS += OPT="-O2 -DBYTE_ORDER=1234 -DLITTLE_ENDIAN=1234"
COMPONENT_BUILD_ARGS += PREFIX="/usr"

COMPONENT_INSTALL_ARGS += PREFIX="/usr"

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
