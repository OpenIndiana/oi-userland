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
COMPONENT_VERSION=	0.58.2
COMPONENT_PROJECT_URL=	http://www.logilab.org/project/logilab-common/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:c92db7d6bbac880969a439027a8239827a02a90815dbfba6bd4c031d85f4cd61
COMPONENT_ARCHIVE_URL=	http://download.logilab.org/pub/common/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/ips.mk
include ../../make-rules/setup.py.mk

# rename pytest to its versioned name; mediated links (depending on
# the python version) in the manifest will create the link from pytest
# to the correct pytest-${PYTHON_VERSION}
COMPONENT_POST_INSTALL_ACTION = \
	(cd $(PROTO_DIR)/usr/bin ; $(MV) -f pytest pytest-$(PYTHON_VERSION))


# common targets

build:		$(BUILD_32)

install:	$(INSTALL_32)
	$(PYTHON.2.6.32) -m compileall $(PROTO_DIR)/usr/lib/python2.6/vendor-packages
	$(PYTHON.2.7.32) -m compileall $(PROTO_DIR)/usr/lib/python2.7/vendor-packages
	
# The tests are run using python 2.7 only and require that the
# python-27 package is installed (does not have to be the default python). 
# Testing using python-26 is done manually, since it requires
# downloading and installing the unittest2 component (not part of Solaris).
# which provides python 2.7 functionality to the unittest python library
# in the python2.6 package.

# Use the python 2.7 libraries (via PYTHONPATH setting) for testing.
test: PYTHON_VERSION=2.7

COMPONENT_TEST_CMD = $(PROTOUSRBINDIR)/pytest-2.7
COMPONENT_TEST_ARGS =

# Expected failures for test target:
# 413 test cases, 1 error, 1 failures, 22 skipped
# 21 modules OK (2 failed)
# failures: unittest_shellutils [1/23], unittest_date [1/45]

test:	$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
