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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		logilab-common
COMPONENT_VERSION=	0.63.2
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.logilab.org/project/logilab-common/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:603ba00c9bb09219a3bd2906c214d9455481110dacc472f450b53d5ae90f28e7
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/1f/36/70463859e7bd8c37c84f1180da665c2ed394dffd22fc696b70681d871380/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/logilab-common

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/setup.py.mk

PYTHON_VERSIONS=2.7

# rename pytest to its versioned name; mediated links (depending on
# the python version) in the manifest will create the link from pytest
# to the correct pytest-${PYTHON_VERSION}
# compile all of the python .py files in the proto area since setup.py doesn't
# seem to be doing it for this component.
COMPONENT_POST_INSTALL_ACTION = \
	(cd $(PROTO_DIR)/usr/bin ; $(MV) -f pytest logilab-pytest-$(PYTHON_VERSION)) ; \
	($(PYTHON) -m compileall $(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES))

build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

# The tests are run using python 2.7 only and require that the
# python-27 package is installed (does not have to be the default python).

# Use the python 2.7 libraries (via PYTHONPATH setting) for testing.
test: PYTHON_VERSION=2.7

COMPONENT_TEST_CMD = $(PROTOUSRBINDIR)/logilab-pytest-2.7
COMPONENT_TEST_ARGS =

# Expected failures for test target:
# Ran 425 test cases 1 errors, 1 failures, 23 skipped
# 20 modules OK (2 failed)
# FAIL: test_site_packages (unittest_modutils.file_from_modpath_tc)
# ERROR: test_locked_for_one_hour (unittest_shellutils.AcquireLockTC)

test:		$(TEST_NO_ARCH)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/pyorbit-27
REQUIRED_PACKAGES += runtime/python-27
