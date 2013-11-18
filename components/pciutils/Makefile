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
# Copyright 2013 Adam Stevko. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		pciutils
COMPONENT_VERSION=	3.2.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:84e705bff712b128a942117565a3506bd4b8bf841d397c1962c6255169762f71
COMPONENT_ARCHIVE_URL=	ftp://atrey.karlin.mff.cuni.cz/pub/linux/pci/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://mj.ucw.cz/sw/pciutils/
COMPONENT_FMRI=		system/pciutils
COMPONENT_SUMMARY=	The PCI Utilities are a collection of programs for inspecting and manipulating configuration of PCI devices
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

COMPONENT_BUILD_GMAKE_ARGS += CC=$(CC) 
COMPONENT_BUILD_GMAKE_ARGS += OPT="-O2 -DBYTE_ORDER=1234 -DLITTLE_ENDIAN=1234"
COMPONENT_BUILD_GMAKE_ARGS += PREFIX="/usr"

COMPONENT_INSTALL_ARGS += PREFIX="/usr"

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)
