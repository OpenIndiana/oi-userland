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
# Copyright 2017 Adam Stevko. All rights reserved.
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		smf-cacert
COMPONENT_VERSION=	20241215
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_VERSION).zip
COMPONENT_SUMMARY=	illumos SMF root certificate service	
COMPONENT_ARCHIVE_URL=  https://github.com/Openindiana/smf-cacert/archive/refs/tags/$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH= sha256:c382a9e5b2f904cae91e00d04eaabbcbb41dcd43f0f2d8c28b2b7bc1e3cc7d7c
COMPONENT_PROJECT_URL=	https://openindiana.org
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_FMRI= system/ca-certificates	
COMPONENT_LICENSE=	CDDL
COMPONENT_LICENSE_FILE=	OPENSOLARIS.LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

COMPONENT_BUILD_ARGS += DESTDIR=$(PROTO_DIR)
COMPONENT_INSTALL_ARGS += DESTDIR=$(PROTO_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/ksh93
