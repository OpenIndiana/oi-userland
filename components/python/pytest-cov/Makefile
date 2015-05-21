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
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pytest-cov
COMPONENT_VERSION=	1.6
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:2e803c89f11e0344111670349f6ef401f831e85cbd287b0c5d61917da5aac454
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://pypi.python.org/pypi/pytest-cov
COMPONENT_BUGDB=	python-mod/pytest-plugins

TPNO=			14503

# pytest-cov itself is Python 3 ready (builds & publishes cleanly with usual
# changes applied) but it depends on cov-core which depends on coverage which
# needs to be upgraded.  Thus, skip Python 3 until then.
PYTHON_VERSIONS=	2.7 2.6

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_TEST_DIR =	$(COMPONENT_SRC)
COMPONENT_TEST_ARGS =	test_pytest_cov.py

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

# Tests require the pytest, coverage and cov-core packages.
test:		$(TEST_NO_ARCH)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

