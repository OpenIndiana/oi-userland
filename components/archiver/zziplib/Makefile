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
# Copyright 2013 Aurelien Larcher.  All rights reserved.
# Copyright 2018 Michal Nowak
# Copyright 2021 Andreas Wacknitz
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zziplib
COMPONENT_VERSION=	0.13.80
COMPONENT_SUMMARY=	zziplib provides read access to zipped files in a zip-archive
COMPONENT_PROJECT_URL=	https://github.com/gdraheim/zziplib
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:21f40d111c0f7a398cfee3b0a30b20c5d92124b08ea4290055fbfe7bdd53a22c
COMPONENT_ARCHIVE_URL=	https://github.com/gdraheim/zziplib/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		compress/zziplib
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_LICENSE=	LGPLv2+
COMPONENT_LICENSE_FILE=	COPYING.LIB

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CMAKE_OPTIONS += -DBUILD_TESTS=ON

# Build dependencies
REQUIRED_PACKAGES += text/xmlto

# Auto-generated dependencies
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
