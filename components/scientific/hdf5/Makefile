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
# Copyright 2016 Gary Mills
# Copyright 2014 (c) Aurelien Larcher. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		hdf5
COMPONENT_VERSION=	1.8.16
COMPONENT_REVISION=	0
COMPONENT_FMRI=		library/c++/hdf5
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_PROJECT_URL=	http://www.hdfgroup.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ed17178abd9928a7237f30370189ba767b9e39e0db45917c2ac4665eb9cb4771
COMPONENT_ARCHIVE_URL=	https://support.hdfgroup.org/ftp/HDF5/releases/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/src/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	$(COMPONENT_FMRI)
COMPONENT_LICENSE=	NCSA
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license
COMPONENT_SUMMARY=	Data model, library, and file format for storing and managing data

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS) -D_LARGEFILE_SOURCE -D__EXTENSIONS__"
CONFIGURE_OPTIONS  +=		--includedir=$(CONFIGURE_PREFIX)/include/hdf5
CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		--enable-fortran
CONFIGURE_OPTIONS  +=		--enable-cxx

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
