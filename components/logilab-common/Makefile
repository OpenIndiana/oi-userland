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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		logilab-common
COMPONENT_VERSION=	0.40.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:4020a550c083f9c4cffdf9bc95f5d957b25ba95b
COMPONENT_ARCHIVE_URL=	http://ftp.logilab.org/pub/common/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/ips.mk
include ../../make-rules/setup.py.mk

# common targets

build:		$(BUILD_32)

install:	$(INSTALL_32)

# Expected failures for test target:
# In unittest_modutils.py, one failure in
# test_knownValues_is_standard_module_2 (unittest_modutils.is_standard_module_tc).
# In unittest_shellutils.py, one error in
# test_locked_for_one_hour (unittest_shellutils.AcquireLockTC).
# Summary: 361 test cases; 1 errors, 1 failures, 28 skipped; 23 modules OK (2 failed)
test:	build
	(cd $(COMPONENT_SRC); $(ENV) - \
	PYTHONPATH=$(PROTO_DIR)/usr/lib/python2.6/vendor-packages \
	bin/pytest test)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
