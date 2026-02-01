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

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= garage
COMPONENT_VERSION= 2.2.0
COMPONENT_SUMMARY= An open-source distributed object storage service tailored for self-hosting
COMPONENT_PROJECT_URL= https://garagehq.deuxfleurs.fr
COMPONENT_SRC= $(COMPONENT_NAME)
COMPONENT_ARCHIVE= $(COMPONENT_SRC)-v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL= https://git.deuxfleurs.fr/Deuxfleurs/garage/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:e68b05d4358008e8b29a0ac235f73e3a12d97d9c6388c330b87282db774c04dc
COMPONENT_FMRI= network/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Web Services/Application and Web Servers

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CLONEY_MODE=copy

PATH= $(PATH.gnu)

COMPONENT_LICENSE= AGPL v3
COMPONENT_LICENSE_FILE= LICENSE

# https://www.illumos.org/issues/15767
LD_Z_IGNORE=

COMPONENT_BUILD_CMD = cargo build --release --target-dir $(BUILD_DIR)/$(MACH64)/target
COMPONENT_BUILD_ENV += SODIUM_USE_PKG_CONFIG=1
COMPONENT_BUILD_ENV += CARGO_PROFILE_RELEASE_LTO=false
COMPONENT_BUILD_ENV += GIT_VERSION=cargo:$(COMPONENT_VERSION)


COMPONENT_INSTALL_ACTION = $(INSTALL) -D $(BUILD_DIR)/$(MACH64)/target/release/garage $(PROTOUSRBINDIR)/garage

# Build dependencies
REQUIRED_PACKAGES+= developer/lang/rustc

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
