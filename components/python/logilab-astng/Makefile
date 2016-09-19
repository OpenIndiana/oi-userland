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

COMPONENT_NAME=		logilab-astng
COMPONENT_VERSION=	0.24.3
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.logilab.org/project/logilab-astng/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:e08fba39689e5a4dfa175749874811e516f019656544874defe05154073f69d4
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/39/ab/3ecd06a186cfc503d9554fdf858e9a320c747cb76432d02e0e802f9450f0/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/logilab-astng

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/setup.py.mk

PYTHON_VERSIONS=	2.7

# common targets

build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

# The tests are run using python 2.7 only and require that
# the python-27 package is installed (does not have to be the default python).

# Use the python 2.7 libraries for testing.
test: PYTHON_VERSION=2.7

# logilab-common is a runtime dependency of logilab-astng,
# and we need to use its latest version from the workspace.
# We can't just add its install target as a dependency here,
# so just run "gmake install" in the logilab-common component directory
# before running logilab-astng tests.
COMPONENT_PRE_TEST_ACTION = ( $(GMAKE) -C \
	$(COMPONENT_DIR)/../logilab-common install )

COMPONENT_TEST_ENV = PYTHONPATH=$(COMPONENT_DIR)/../logilab-common/build/prototype/$(MACH)$(PYTHON_VENDOR_PACKAGES):$(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES)

# Run pytest-2.7 from logilab-common's proto area for now, until the
# new version of logilab-common containing pytest is in CBE.
# Then we can change it to /usr/bin/pytest-$(PYTHON_VERSION).
COMPONENT_TEST_CMD = $(COMPONENT_DIR)/../logilab-common/build/prototype/$(MACH)/usr/bin/pytest-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =

# Expected failures for test target:
# 249 test cases in 1.30s, 1 failures, 5 skipped
# FAIL: test_numpy_crash

test:		$(TEST_NO_ARCH)

REQUIRED_PACKAGES += runtime/python-27
