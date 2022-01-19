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
# Copyright 2022 Friedrich Kink
#

BUILD_BITS=             64
BUILD_STYLE=            configure

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tre
COMPONENT_VERSION=	0.8.0
COMPONENT_SUMMARY=	TRE - The free and portable approximate regex matching library.
COMPONENT_PROJECT_URL=	https://laurikari.net/tre/tre-0-8-0-released/
COMPONENT_FMRI=		library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=	http://laurikari.net/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=sha256:8dc642c2cde02b2dac6802cdbe2cda201daf79c4ebcbb3ea133915edf1636658
COMPONENT_LICENSE=	Copyright (c) 2001-2009 Ville Laurikari <vl@iki.fi>
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_TRANSFORMS += '-ne "/^All/p" '

REQUIRED_PACKAGES += system/library
