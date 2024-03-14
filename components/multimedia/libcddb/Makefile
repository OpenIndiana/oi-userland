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
# Copyright 2015 Alexander Pyhalov
#

BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libcddb
COMPONENT_VERSION=	1.3.2
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://libcddb.sourceforge.net/
COMPONENT_SUMMARY=	C library to access data on a CDDB server
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:68e9b53918b9bea727fb2db78936526671c039dcd7396cb82ecd6854e866048c
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/libcddb/files/libcddb/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_LICENSE=	LGPLv2
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_FMRI= 	library/audio/libcddb 

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --without-cdio

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
