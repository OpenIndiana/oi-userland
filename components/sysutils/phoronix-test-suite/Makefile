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
COMPONENT_VERSION=10.8.4
COMPONENT_SUMMARY=The Phoronix Test Suite open-source, cross-platform automated testing/benchmarking software.
COMPONENT_PROJECT_URL=https://github.com/phoronix-test-suite/phoronix-test-suite
COMPONENT_FMRI= benchmark/phoronix-test-suite
COMPONENT_CLASSIFICATION= Development/System
COMPONENT_SRC=$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=https://github.com/phoronix-test-suite/phoronix-test-suite/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=sha256:7b5da7193c0190c648fc0c7ad6cdfbde5d935e88c7bfa5e99cd3a720cd5e2c5a
COMPONENT_LICENSE=GPLv3
COMPONENT_LICENSE_FILE=phoronix.license

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ACTION=pwd
COMPONENT_INSTALL_ACTION=cd $(@D) && bash $(@D)/install-sh $(PROTO_DIR)/usr

# Build dependencies
REQUIRED_PACKAGES+=web/php-82/php-cli
# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
