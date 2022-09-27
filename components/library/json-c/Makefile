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
# Copyright 2013 Adam Stevko. All rights reserved.
# Copyright 2022 Niklas Poslovski
#
BUILD_STYLE=cmake
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		json-c
COMPONENT_FMRI=		library/json-c
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	MIT
COMPONENT_VERSION=	0.16
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:8e45ac8f96ec7791eaf3bb7ee50e9c2100bbbc87b8d0f1d030c5ba8a0288d96b
COMPONENT_PROJECT_URL=	https://github.com/json-c/json-c
COMPONENT_ARCHIVE_URL=	https://s3.amazonaws.com/json-c_releases/releases/$(COMPONENT_ARCHIVE)
COMPONENT_SUMMARY=	A JSON implementation in C

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
