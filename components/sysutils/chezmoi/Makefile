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
# Copyright 2021 Benjamin S. Osenbach
#
BUILD_BITS=64 # for binaries or 32_and_64 for libraries
BUILD_STYLE=justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=chezmoi
COMPONENT_VERSION=2.7.5
COMPONENT_SUMMARY=Manage your dotfiles across multiple diverse machines, securely.
COMPONENT_PROJECT_URL=https://github.com/twpayne/chezmoi
COMPONENT_FMRI=application/chezmoi
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=https://github.com/twpayne/chezmoi/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=sha256:ed9de88a851cbbb2acce77e13615fe45a19350112f58d9acc268b2ff4961d8ab
COMPONENT_LICENSE=MIT
COMPONENT_LICENSE_FILE=chezmoi.license
TEST_TARGET=$(NO_TESTS) # if no testsuite enabled
include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ENV += GOOS="illumos"
COMPONENT_BUILD_ENV += GOPATH="$(SOURCE_DIR)/gopath"
COMPONENT_BUILD_ENV += GOBIN="$(PROTO_DIR)/usr/bin"

COMPONENT_INSTALL_ENV += GOOS="illumos"
COMPONENT_INSTALL_ENV += GOPATH="$(SOURCE_DIR)/gopath"
COMPONENT_INSTALL_ENV += GOBIN="$(PROTO_DIR)/usr/bin"

# Go doesn't like symbolic links, so copy the source directory
COMPONENT_COPY_ACTION=(cp -rL $(SOURCE_DIR)/* $(@D))

# Build dependencies
REQUIRED_PACKAGES+=developer/golang
REQUIRED_PACKAGES+=developer/versioning/git
# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
