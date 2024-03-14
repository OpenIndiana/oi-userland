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
# Copyright 2011, EveryCity Ltd. All rights reserved.
# Copyright 2013, Adam Stevko. All rights reserved.
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cabextract
COMPONENT_VERSION=	1.11
COMPONENT_SUMMARY=	cabextract - extract Microsoft cabinet files
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:b5546db1155e4c718ff3d4b278573604f30dd64c3c5bfd4657cd089b823a3ac6
COMPONENT_PROJECT_URL=	https://www.cabextract.org.uk/
COMPONENT_ARCHIVE_URL=	https://www.cabextract.org.uk/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	archiver/cabextract
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
