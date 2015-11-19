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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

COMPONENT_NAME=		CherryPy
COMPONENT_VERSION=	3.8.0
COMPONENT_PROJECT_URL=	http://www.cherrypy.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ffcdb43667d4098247efaf8c82dd36d3dd4f8e5dc768ef5e90b480899e523bea
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_BUGDB=	python-mod/cherrypy

TPNO=			25174

PATCH_LEVEL=0

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_POST_INSTALL_ACTION = \
	(cd $(PROTO_DIR)/usr/bin ; $(MV) cherryd cherryd$(PYTHON_VERSION))

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_DIR = 	$(SOURCE_DIR)/cherrypy/test
COMPONENT_TEST_CMD =	nosetests -s ./
COMPONENT_TEST_ARGS = 

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

# test are not clean, so not appropriate to run at top level
$(SKIP_TEST_AT_TOP_LEVEL)

# The test requires some interactive selections from the users to continue,
# otherwise it'll hang.
# Ran 246 tests, 3 skipped, 3 failures 
# FAIL: test_598, test_queue_full, test_2_File_Concurrency
test:		$(TEST_NO_ARCH)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += system/core-os
