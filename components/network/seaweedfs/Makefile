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

COMPONENT_NAME= seaweedfs
COMPONENT_VERSION= 4.0.7
HUMAN_VERSION= 4.07
COMPONENT_SUMMARY= SeaweedFS is a fast distributed storage system for blobs, objects, files
COMPONENT_PROJECT_URL= https://github.com/seaweedfs/seaweedfs
COMPONENT_SRC= $(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= $(COMPONENT_PROJECT_URL)/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:0689e47a1906d14f6149652bd7dad659ff92567ab88b43b8d533a462d750db4a
COMPONENT_FMRI= network/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Web Services/Application and Web Servers

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CLONEY_MODE=copy

PATH= $(PATH.gnu)
PATH.prepend = /usr/bin

COMPONENT_LICENSE= Apache-2.0
COMPONENT_LICENSE_FILE= LICENSE

COMPONENT_BUILD_ENV += GOOS="illumos"
COMPONENT_BUILD_ENV += GOPATH="$(BUILD_DIR)/$(MACH64)/gopath"
COMPONENT_BUILD_ENV += PATH="$(BUILD_DIR)/$(MACH64)/gopath/bin:$(PATH)"
COMPONENT_BUILD_ENV += PREFIX=/usr
COMPONENT_BUILD_ENV += HOME=/tmp

COMPONENT_INSTALL_ENV += GOOS="illumos"
COMPONENT_INSTALL_ENV += GOPATH="$(BUILD_DIR)/$(MACH64)/gopath"
COMPONENT_INSTALL_ENV += PATH="$(BUILD_DIR)/$(MACH64)/gopath/bin:$(PATH)"
COMPONENT_INSTALL_ENV += PREFIX=/usr
COMPONENT_INSTALL_ENV += HOME=/tmp

COMPONENT_POST_INSTALL_ACTION = $(INSTALL) -D $(BUILD_DIR)/$(MACH64)/gopath/bin/weed $(PROTOUSRBINDIR)/weed

# Build dependencies
REQUIRED_PACKAGES+=developer/golang

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
