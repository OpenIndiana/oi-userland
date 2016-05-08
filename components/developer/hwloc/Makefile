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
# Copyright 2016 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=          hwloc
COMPONENT_VERSION=       1.11.3
COMPONENT_SUMMARY=       hwloc - Portable Hardware Locality
COMPONENT_PROJECT_URL=   https://www.open-mpi.org/projects/hwloc/
COMPONENT_FMRI=          developer/hwloc
COMPONENT_CLASSIFICATION=Development/High Performance Computing
COMPONENT_SRC=           $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=       $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=   https://www.open-mpi.org/software/hwloc/v1.11/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:e7748e4412fb94cf22fd1971de939d9770e6068f7003dea107417f21146333fa
COMPONENT_LICENSE=      BSD-2
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_ENV=+ENV=/usr/bin/env

CONFIGURE_OPTIONS+= --enable-cairo
CONFIGURE_OPTIONS+= --enable-cpuid
CONFIGURE_OPTIONS+= --enable-libxml2
CONFIGURE_OPTIONS+= --enable-pci


build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)
