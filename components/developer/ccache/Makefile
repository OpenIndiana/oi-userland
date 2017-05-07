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
# Copyright (c) 2015-2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ccache
COMPONENT_VERSION=	3.3.3
COMPONENT_PROJECT_URL=	http://ccache.samba.org/
COMPONENT_DOWNLOAD_URL=	http://samba.org/ftp/$(COMPONENT_NAME)/
COMPONENT_DOCUMENTATION_URL =	http://ccache.samba.org/manual.html
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:2985bc5e32ebe38d2958d508eb54ddcad39eed909489c0c2988035214597ca54
COMPONENT_ARCHIVE_URL=	$(COMPONENT_DOWNLOAD_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_SUMMARY=	ccache - cacher of GCC-compiled files to avoid doing the same job twice
COMPONENT_FMRI=		developer/ccache
COMPONENT_CLASSIFICATION=	Development/C
COMPONENT_LICENSE=	"GPLv3,murmurhash,papowell/jhweiss,PostgreSQL,Python,zlib"
COMPONENT_LICENSE_FILE=	LICENSE.txt

CFLAGS  +=			-D_GNU_SOURCE -D__EXTENSIONS__ --std=c99

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_OPTIONS +=	--sysconfdir=/etc

# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
