#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 (c) Aurelien Larcher. All rights reserved.
# Copyright 2023 (c) Andreas Wacknitz
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           hdf5
COMPONENT_MJR_VERSION=    1.14
COMPONENT_BLD_VERSION=    $(COMPONENT_MJR_VERSION).5
COMPONENT_VERSION=        $(COMPONENT_BLD_VERSION)
#HUMAN_VERSION=			  $(COMPONENT_MJR_VERSION).5
COMPONENT_SUMMARY=        HDF5 - Data model, library, and file format for storing and managing data
COMPONENT_PROJECT_URL=    https://www.hdfgroup.org
COMPONENT_SRC=            $(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=    https://github.com/HDFGroup/hdf5/releases/download/hdf5_$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=   sha256:ec2e13c52e60f9a01491bb3158cb3778c985697131fc6a342262d32a26e58e44
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_FMRI=           library/c++/hdf5
COMPONENT_LICENSE=        NCSA
COMPONENT_LICENSE_FILE=   COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS) -D_LARGEFILE_SOURCE -D__EXTENSIONS__"
CONFIGURE_OPTIONS += --includedir=$(CONFIGURE_PREFIX)/include/hdf5
CONFIGURE_OPTIONS += --with-default-plugindir=$(CONFIGURE_PREFIX)/share/hdf5/plugins
CONFIGURE_OPTIONS += --with-examplesdir=$(CONFIGURE_PREFIX)/share/hdf5/examples
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-fortran
CONFIGURE_OPTIONS += --enable-cxx

COMPONENT_TEST_TRANSFORMS += \
	' -e "/Testing/p" ' \
	' -e "/passed/p" ' \
	' -e "/skipped/p" ' \
	' -e "/=====/p" ' \
	' -e "/finished/p" ' \
	' -e "/Test log/p" ' \
	' -e "/Test sizes/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GFORTRAN_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
