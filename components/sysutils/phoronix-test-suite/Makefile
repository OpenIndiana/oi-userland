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
# Copyright 2022 Benjamin S Osenbach
#
BUILD_BITS=64 # for binaries or 32_and_64 for libraries
BUILD_STYLE=justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=phoronix-test-suite
COMPONENT_VERSION=10.8.6
COMPONENT_COMMIT=be12163bb02435219d4fd891cd6258597ca9bc2f
COMPONENT_SUMMARY=The Phoronix Test Suite open-source, cross-platform automated testing/benchmarking software.
COMPONENT_PROJECT_URL=https://github.com/phoronix-test-suite/phoronix-test-suite
COMPONENT_FMRI= benchmark/phoronix-test-suite
COMPONENT_CLASSIFICATION= Development/System
COMPONENT_SRC=$(COMPONENT_NAME)-$(COMPONENT_COMMIT)
COMPONENT_ARCHIVE=$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=https://codeload.github.com/phoronix-test-suite/phoronix-test-suite/tar.gz/$(COMPONENT_COMMIT)
COMPONENT_ARCHIVE_HASH=sha256:da60ce3099c26eceb53c26d16e30e3e611868ac0dbc24d28558d98f9564ea2f6
COMPONENT_LICENSE=GPLv3
COMPONENT_LICENSE_FILE=phoronix.license

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ACTION=:
COMPONENT_INSTALL_ACTION=cd $(@D) && DESTDIR=$(PROTO_DIR) sh ./install-sh /usr

# Build dependencies
REQUIRED_PACKAGES+=web/php-84/php-cli
# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
