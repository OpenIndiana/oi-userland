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
# Copyright 2022 Gary Mills
#
BUILD_BITS= 64
BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zrepl
COMPONENT_VERSION=	0.6.1
COMPONENT_SUMMARY=	A one-stop, integrated solution for ZFS replication
COMPONENT_PROJECT_URL=	https://zrepl.github.io/
COMPONENT_FMRI=		backup/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/$(COMPONENT_NAME)/$(COMPONENT_NAME)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:263c82501b75a1413f8a298c1d67d7e940c1b0cb967979790773237e2a30adbd
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

DATE=$(shell date -u +%Y-%m-%d-T%TZ)

# The directory specified by the GOPATH environment variable must not
# exist, or be empty.  During the "build" target, the GO compiler
# downloads GO modules to subdirectories of this directory.  This
# behavior is how GO resolves external symbols.

COMPONENT_BUILD_ENV += GOOS="illumos"
COMPONENT_BUILD_ENV += GOPATH="$(SOURCE_DIR)/gopath"
COMPONENT_BUILD_ENV += PREFIX=/usr
COMPONENT_BUILD_ENV += VERSION="v$(COMPONENT_VERSION)"
COMPONENT_BUILD_ENV += DATE="'$(DATE)'"
COMPONENT_BUILD_ENV += BUILT_BY="oi-userland"

COMPONENT_INSTALL_ENV += GOOS="illumos"
COMPONENT_INSTALL_ENV += GOPATH="$(SOURCE_DIR)/gopath"
COMPONENT_INSTALL_ENV += PREFIX=/usr
COMPONENT_INSTALL_ENV += VERSION="v$(COMPONENT_VERSION)"
COMPONENT_INSTALL_ENV += DATE="'$(DATE)'"
COMPONENT_INSTALL_ENV += BUILT_BY="oi-userland"

# All installed files go to the artifact directory
COMPONENT_INSTALL_ARGS += ARTIFACTDIR=$(PROTO_DIR)

# Pre-create all the install directories
COMPONENT_PRE_INSTALL_ACTION=$(MKDIR) "$(PROTO_DIR)/usr/bin" \
    "$(PROTO_DIR)/usr/share/bash-completion/completions" \
    "$(PROTO_DIR)/usr/share/zsh/site-functions" \
    "$(PROTO_DIR)/usr/share/man/man5" \
    "$(PROTO_DIR)/usr/share/man/man8" \
    "$(PROTO_DIR)/usr/share/zrepl/config";

# Install sample config files
COMPONENT_POST_INSTALL_ACTION=$(CP) $(COMPONENT_DIR)/files/illumos.yml \
    $(SOURCE_DIR)/config/samples/*.yml \
    $(PROTO_DIR)/usr/share/zrepl/config

# Add the files directory to the prototype search path list
PKG_PROTO_DIRS += $(COMPONENT_DIR)/files

# Build dependencies
REQUIRED_PACKAGES += developer/golang
REQUIRED_PACKAGES += library/python/docutils

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
