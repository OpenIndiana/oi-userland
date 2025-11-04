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

COMPONENT_NAME= minio
COMPONENT_VERSION= 25.9
HUMAN_VERSION= 2025-09-07T16-13-09Z
COMPONENT_GIT_REV=07c3a429bfed433e49018cb0f78a52145d4bedeb
COMPONENT_SUMMARY= MinIO is a high-performance, S3 compatible object store, open sourced under GNU AGPLv3 license.
COMPONENT_PROJECT_URL= https://github.com/minio/minio
COMPONENT_SRC= $(COMPONENT_NAME)-RELEASE.$(HUMAN_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= $(COMPONENT_PROJECT_URL)/archive/refs/tags/RELEASE.$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:c9598dcce3440977e79f787f2ba0e7e4d92c8d556bd51e7cef3785bafd6635f3
COMPONENT_FMRI= network/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Web Services/Application and Web Servers

include $(WS_MAKE_RULES)/common.mk

CLONEY_MODE=copy

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_LICENSE= AGPL v3
COMPONENT_LICENSE_FILE= LICENSE

LDFLAGS = -s -w \
  -X github.com/minio/minio/cmd.Version=$(HUMAN_VERSION) \
  -X github.com/minio/minio/cmd.CopyrightYear=$(shell echo $(HUMAN_VERSION) | cut -c1-4) \
  -X github.com/minio/minio/cmd.ReleaseTag=RELEASE.$(HUMAN_VERSION) \
  -X github.com/minio/minio/cmd.CommitID=$(COMPONENT_GIT_REV) \
  -X github.com/minio/minio/cmd.ShortCommitID=$(shell echo $(COMPONENT_GIT_REV) | cut -c1-12)

COMPONENT_BUILD_ENV += GOOS="illumos"
COMPONENT_BUILD_ENV += GOPATH="$(@D)/gopath"
COMPONENT_BUILD_ENV += HOME=/tmp
COMPONENT_BUILD_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_INSTALL_ENV += GOOS="illumos"
COMPONENT_INSTALL_ENV += GOPATH="$(@D)/gopath"
COMPONENT_INSTALL_ENV += HOME=/tmp
COMPONENT_INSTALL_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_POST_INSTALL_ACTION = $(INSTALL) -D $(@D)/gopath/bin/minio $(PROTOUSRBINDIR)/minio

# Build dependencies
REQUIRED_PACKAGES+=developer/golang

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
