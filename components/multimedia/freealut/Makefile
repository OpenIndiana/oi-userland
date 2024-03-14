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
# Copyright 2018 Harry Liebel <hliebel@gmail.com>
#

BUILD_BITS= 64
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		freealut
COMPONENT_VERSION=	1.1.0
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	The OpenAL Utility Toolkit
COMPONENT_DESCRIPTION=	Freealut is a free implementation of OpenAL's ALUT standard.
COMPONENT_PROJECT_URL=	https://openal.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_NAME)_1_1_0
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)_1_1_0.tar.gz
COMPONENT_ARCHIVE_HASH= sha256:c3880d7dbb90c7db54e1d6b88aa0a34dd9e2d828fd389be0d2cbb2632b0885dd
COMPONENT_ARCHIVE_URL=	https://github.com/vancegroup/$(COMPONENT_NAME)/archive/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/audio/freealut
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE=	LGPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/openal
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
