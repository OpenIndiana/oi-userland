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
# Copyright 2017 Dariusz Sendkowski
# Copyright 2023 Andreas Wacknitz
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           netcdf-c
COMPONENT_VERSION=        4.9.2
COMPONENT_SUMMARY=        A set of software libraries and self-describing, machine-independent data formats. 
COMPONENT_DESCRIPTION=    NetCDF (Network Common Data Form) is a set of software libraries and machine-independent data formats \
	that support the creation, access, and sharing of array-oriented scientific data.
COMPONENT_PROJECT_URL=    https://www.unidata.ucar.edu/software/netcdf/ 
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=   sha256:bc104d101278c68b303359b3dc4192f81592ae8640f1aee486921138f7f88cb7
COMPONENT_ARCHIVE_URL=    https://github.com/Unidata/netcdf-c/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=           library/netcdf-c
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=        UCAR 
COMPONENT_LICENSE_FILE=   COPYRIGHT

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS) -I/usr/include/hdf5"
CONFIGURE_OPTIONS += --disable-dependency-tracking
CONFIGURE_OPTIONS += --enable-static=no
CONFIGURE_OPTIONS += --enable-hdf5
CONFIGURE_OPTIONS += --with-plugin-dir=/usr/share/netcdf-c/plugins

unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/c++/hdf5
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libzip
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
