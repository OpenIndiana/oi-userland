#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END

#
# Copyright 2021 Gary Mills
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rdiff-backup
COMPONENT_VERSION=	2.0.5
# COMPONENT_REVISION=	0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:fd3af3d39fe91ef2b281e6a906445112c5b718640e490c8b6f83a8960318352b
COMPONENT_ARCHIVE_URL=	https://github.com/$(COMPONENT_NAME)/$(COMPONENT_NAME)/archive/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://rdiff-backup.net/
COMPONENT_BUGDB=	utility/rdiff-backup

# This version of rdiff-backup supports python versions: 3.5 3.6 3.7 3.8
PYTHON_VERSIONS=	3.7

# Copy static files to destination directories
COMPONENT_POST_INSTALL_ACTION = ( \
cd $(PROTO_DIR); \
$(MKDIR) -m 0755 usr/share/doc/rdiff-backup-$(COMPONENT_VERSION) \
  usr/share/bash-completion/completions usr/share/man/man1; \
for V in $(PYTHON_VERSIONS); \
do \
  for N in CHANGELOG.md COPYING FAQ.md README.md; \
  do \
    $(CP) -p usr/lib/python$$V/vendor-packages/share/doc/rdiff-backup/$$N \
      usr/share/doc/rdiff-backup-$(COMPONENT_VERSION); \
  done; \
  $(CP) -p usr/lib/python$$V/vendor-packages/share/bash-completion/completions/rdiff-backup \
    usr/share/bash-completion/completions; \
  $(CP) -p usr/lib/python$$V/vendor-packages/share/man/man1/rdiff-backup-statistics.1 \
    usr/share/man/man1; \
  $(CP) -p usr/lib/python$$V/vendor-packages/share/man/man1/rdiff-backup.1 \
    usr/share/man/man1; \
done \
)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk
include $(WS_TOP)/make-rules/setup.py.mk

# common targets

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/librsync
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += system/library
