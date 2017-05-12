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
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           netcdf
COMPONENT_VERSION=        4.4.1.1
COMPONENT_FMRI=           library/netcdf
COMPONENT_SUMMARY=	A set of software libraries and self-describing, machine-independent data formats. 
COMPONENT_PROJECT_URL=   http://www.unidata.ucar.edu/software/netcdf/ 
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:4d44c6f4d02a8faf10ea619bfe1ba8224cd993024f4da12988c7465f663c8cae
COMPONENT_ARCHIVE_URL= ftp://ftp.unidata.ucar.edu/pub/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=       UCAR 
COMPONENT_LICENSE_FILE= COPYRIGHT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS  +=	CFLAGS="$(CFLAGS) -I/usr/include/hdf5"

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TEST)


REQUIRED_PACKAGES += library/c++/hdf5
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
