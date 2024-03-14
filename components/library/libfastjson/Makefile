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
COMPONENT_VERSION=	1.2304.0
COMPONENT_SUMMARY=	A performance-focused json library for C
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:6c18848c75b179108429fc2818273551c68ffe6ddd5e414c20c071c844befbc1
COMPONENT_PROJECT_URL=	https://github.com/rsyslog/libfastjson
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/libfastjson
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static

COMPONENT_PREP_ACTION = ( cd $(@D)  && ./autogen.sh)

COMPONENT_PRE_CONFIGURE_ACTION = ( cp -r $(SOURCE_DIR)/* $(@D) )

unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
