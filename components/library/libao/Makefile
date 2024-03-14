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
# Copyright 2017 Aurelien Larcher
#

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=        libao
COMPONENT_VERSION=     1.2.2
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=     libao - cross-platform audio library
COMPONENT_PROJECT_URL= https://www.xiph.org/ao/
COMPONENT_FMRI=        library/audio/libao
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_SRC=         $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=     $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= https://github.com/xiph/libao/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:df8a6d0e238feeccb26a783e778716fb41a801536fe7b6fce068e313c0e2bf4d
COMPONENT_LICENSE=	GPL-2.0-only
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= ( cd $(@D); PATH="$(PATH)" sh autogen.sh )

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += system/library
