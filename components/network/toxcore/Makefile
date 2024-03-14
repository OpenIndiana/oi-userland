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
# Copyright 2022-2023 Niklas Poslovski
#

BUILD_STYLE=cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         toxcore
COMPONENT_VERSION=      0.2.18
#COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=  https://tox.chat
COMPONENT_SUMMARY=      Secure, configuration-free, P2P Skype replacement backend
COMPONENT_FMRI=         network/chat/toxcore
COMPONENT_SRC=          c-toxcore-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:1fba883638fd18985fd41acd35fed198c2cdd6e91651eb1c3fe602b610b535fe
COMPONENT_ARCHIVE_URL=	https://github.com/TokTok/c-toxcore/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=       Applications/Internet
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= LICENSE

GIT_BRANCH_1=           4c3737d1a172ee74d2b35b5fd6865d1fe9dac7af
COMPONENT_SRC_1=        cmp-$(GIT_BRANCH_1)
COMPONENT_ARCHIVE_1=    $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_URL_1=https://github.com/camgunz/cmp/archive/$(GIT_BRANCH_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:a13a479f747854b990cee074cdc7a7309ec6e025059b7213b9ca311860de1b02

COMPONENT_POST_UNPACK_ACTION_1= \
        mv $(COMPONENT_SRC_1)/* $(SOURCE_DIR)/third_party/cmp

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libconfig
REQUIRED_PACKAGES += library/opus
REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += library/video/libvpx
REQUIRED_PACKAGES += system/library
