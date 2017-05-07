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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= patchutils

COMPONENT_VERSION= 0.3.3
COMPONENT_SUMMARY= patchutils - Tools for manipulating patch files
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:91f4e8451b2efcac5d40c966e42c175803450f0de94c926bfecc12c90070ad3c
COMPONENT_ARCHIVE_URL= \
  http://cyberelk.net/tim/data/patchutils/stable/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://cyberelk.net/tim/software/patchutils/

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL = 0

CONFIGURE_OPTIONS +=	--with-patch=gpatch
CONFIGURE_OPTIONS +=	--with-diff=gdiff

COMPONENT_TEST_ENV += PATH=/usr/bin:/usr/gnu/bin:/opt/dtbld/bin

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(TEST_32)
