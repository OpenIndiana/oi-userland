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
# Copyright 2025 Jiwon Na
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           libhangul
COMPONENT_VERSION=        0.1.0
IPS_COMPONENT_VERSION= 0.5.11
COMPONENT_REVISION= 1
COMPONENT_GIT_REV=	154a5e0
COMPONENT_SUMMARY=        libhangul - A library to support hangul input method logic
COMPONENT_SRC=		libhangul-$(COMPONENT_GIT_REV)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=   sha256:d5d4ee0e8e5ab30e5d190b1bc989b943a044844b95bd83b5533de550fd7af3b9
COMPONENT_ARCHIVE_URL=    https://codeload.github.com/libhangul/$(COMPONENT_NAME)/tar.gz/$(COMPONENT_GIT_REV)
COMPONENT_FMRI=           system/input-method/library/libhangul
COMPONENT_CLASSIFICATION= System/Localizations
COMPONENT_LICENSE=        LGPL v2.1
COMPONENT_LICENSE_FILE=   COPYING
COMPONENT_PROJECT_URL=    https://github.com/libhangul/libhangul

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION =       ( cd $(SOURCE_DIR) && ./autogen.sh )

CONFIGURE_OPTIONS += --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += system/library
