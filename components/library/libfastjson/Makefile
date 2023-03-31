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
# Copyright 2022 Niklas Poslovski
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libfastjson
COMPONENT_VERSION=	0.99.9.1
COMPONENT_SUMMARY=	A performance-focused json library for C
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:67cde7e85fa372036d7694f3b32cfc666705ab19367920f555af9d1c183edfef
COMPONENT_PROJECT_URL=	https://github.com/rsyslog/libfastjson
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/libfastjson
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	MIT

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static

COMPONENT_PREP_ACTION = ( cd $(@D)  && ./autogen.sh)

COMPONENT_PRE_CONFIGURE_ACTION = ( cp -r $(SOURCE_DIR)/* $(@D) )

unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
