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

COMPONENT_NAME= minio-client
COMPONENT_VERSION= 25.8
HUMAN_VERSION= 2025-08-13T08-35-41Z
COMPONENT_GIT_REV= 7394ce0dd2a80935aded936b09fa12cbb3cb8096
COMPONENT_SUMMARY= Unix like utilities for object store
COMPONENT_PROJECT_URL= https://github.com/minio/mc
COMPONENT_SRC= mc-RELEASE.$(HUMAN_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= $(COMPONENT_PROJECT_URL)/archive/refs/tags/RELEASE.$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:29db22500374169a43951c7cef09daf19e7291ea5ba00ac10f321371b0a35b32
COMPONENT_FMRI= network/minio/client
COMPONENT_CLASSIFICATION= Applications/Internet

include $(WS_MAKE_RULES)/common.mk

CLONEY_MODE=copy

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_LICENSE= AGPL v3
COMPONENT_LICENSE_FILE= LICENSE

LDFLAGS = -s -w \
  -X github.com/minio/mc/cmd.Version=$(HUMAN_VERSION) \
  -X github.com/minio/mc/cmd.CopyrightYear=$(shell echo $(HUMAN_VERSION) | cut -c1-4) \
  -X github.com/minio/mc/cmd.ReleaseTag=RELEASE.$(HUMAN_VERSION) \
  -X github.com/minio/mc/cmd.CommitID=$(COMPONENT_GIT_REV) \
  -X github.com/minio/mc/cmd.ShortCommitID=$(shell echo $(COMPONENT_GIT_REV) | cut -c1-12)


COMPONENT_BUILD_ENV += GOOS="illumos"
COMPONENT_BUILD_ENV += GOPATH="$(@D)/gopath"
COMPONENT_BUILD_ENV += HOME=/tmp
COMPONENT_BUILD_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_INSTALL_ENV += GOOS="illumos"
COMPONENT_INSTALL_ENV += GOPATH="$(@D)/gopath"
COMPONENT_INSTALL_ENV += HOME=/tmp
COMPONENT_INSTALL_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_POST_INSTALL_ACTION = $(INSTALL) -D $(@D)/gopath/bin/mc $(PROTOUSRBINDIR)/minio-client

# Build dependencies
REQUIRED_PACKAGES+=developer/golang

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
