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
# Copyright 2022 Niklas Poslovski
#

BUILD_BITS=64
BUILD_STYLE=cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         toxcore
COMPONENT_VERSION=      0.2.17
#COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=  https://tox.chat
COMPONENT_SUMMARY=      Secure, configuration-free, P2P Skype replacement backend
COMPONENT_FMRI=         network/chat/toxcore
COMPONENT_SRC=          c-toxcore-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:d9cdf5d690fe8e217dcaba5b988fb943bbe7bda919a2fde6d9506df047e5f4cb
COMPONENT_ARCHIVE_URL=	https://github.com/TokTok/c-toxcore/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=       Applications/Internet
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= toxcore.license

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libconfig
REQUIRED_PACKAGES += library/msgpack
REQUIRED_PACKAGES += library/opus
REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += library/video/libvpx
REQUIRED_PACKAGES += system/library
