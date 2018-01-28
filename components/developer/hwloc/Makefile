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
COMPONENT_VERSION=       1.11.8
COMPONENT_REVISION=      1
COMPONENT_SUMMARY=       hwloc - Portable Hardware Locality
COMPONENT_PROJECT_URL=   https://www.open-mpi.org/projects/hwloc/
COMPONENT_FMRI=          developer/hwloc
COMPONENT_CLASSIFICATION=Development/High Performance Computing
COMPONENT_SRC=           $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=       $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=   https://www.open-mpi.org/software/hwloc/v1.11/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:ecef10265084d9123dc0b03d82ff5ee06fbf5ba755a912e7511ae590c9ee594d
COMPONENT_LICENSE=      BSD-2

# When CONFIGURE_FIX_LIBTOOL_RPATH is integrated, we can remove local fix and enable it
CONFIGURE_FIX_LIBTOOL_RPATH = no

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS+= --enable-cairo
CONFIGURE_OPTIONS+= --enable-cpuid
CONFIGURE_OPTIONS+= --enable-libxml2
CONFIGURE_OPTIONS+= --enable-pci

CONFIGURE_ENV.64 += LT_SYS_LIBRARY_PATH="/lib/$(MACH64):/usr/lib/$(MACH64)"

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
