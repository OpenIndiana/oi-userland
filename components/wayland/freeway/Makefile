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
# Copyright 2026 Benjamin S. Osenbach
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= freeway
COMPONENT_VERSION= 1.23.0
COMPONENT_COMMIT= 93158892cf02ebf8b95498a46c5ec9d3a9cf9991
COMPONENT_SUMMARY= Freeway is a small and portable implementation of the Wayland protocol for POSIX-compliant operating systems
COMPONENT_PROJECT_URL= https://git.sr.ht/~shrub900/freeway
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_COMMIT)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= https://git.sr.ht/~shrub900/freeway/archive/$(COMPONENT_COMMIT).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:a8381ac5ae7f6acd2624a20be12952f737be38536392d67f30c755286a3a9136
COMPONENT_FMRI= wayland/freeway
COMPONENT_CLASSIFICATION= System/Wayland
COMPONENT_LICENSE= MIT
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CFLAGS += -Wno-error=implicit-function-declaration

COMPONENT_BUILD_ENV += PREFIX=/usr

COMPONENT_INSTALL_ENV += PREFIX=/usr

# Auto-generated dependencies
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += system/library
