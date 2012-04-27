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

#
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		logilab-common
COMPONENT_VERSION=	0.40.0
COMPONENT_PROJECT_URL=	http://www.logilab.org/project/logilab-common/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0529201ad23ea4a57e72a4d4e6607cc440b5086b25c69d01db8ef6d1c9cc9c57
COMPONENT_ARCHIVE_URL=	http://ftp.logilab.org/pub/common/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/ips.mk
include ../../make-rules/setup.py.mk

# common targets

build:		$(BUILD_32)

install:	$(INSTALL_32)
	$(PYTHON.2.6.32) -m compileall $(PROTO_DIR)/usr/lib/python2.6/vendor-packages
	$(PYTHON.2.7.32) -m compileall $(PROTO_DIR)/usr/lib/python2.7/vendor-packages
	

# Expected failures for test target:
# 722 test cases, 17 errors, 5 failures, 56 skipped
# 43 modules OK (7 failed)
COMPONENT_TEST_DIR = $(COMPONENT_SRC)
COMPONENT_TEST_CMD = bin/pytest
COMPONENT_TEST_ARGS = test

test:	$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
