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
# Copyright 2021 Gary Mills
#

BUILD_STYLE=	setup.py
BUILD_BITS=	NO_ARCH

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		astroid
COMPONENT_VERSION=	2.6.2
# COMPONENT_REVISION=	0
COMPONENT_PROJECT_URL=	https://github.com/PyCQA/astroid
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:0b146fca525affa936312de8e2e196e92562527f389fcd86f66bf1c8b5cd1a0e
COMPONENT_ARCHIVE_URL=	https://github.com/PyCQA/$(COMPONENT_NAME)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_BUGDB=	python-mod/astroid

# Set python version used by this product
PYTHON_VERSION=		3.9
PYTHON_VERSIONS=	3.9

include $(WS_MAKE_RULES)/common.mk

# The tests are run using python 3.9 only and require that the
# python-39 package is installed (does not have to be the default python).
# The pytest-39 package must also be installed

# Use the python 3.9 libraries (via PYTHONPATH setting) for testing.
test: PYTHON_VERSION=3.9

COMPONENT_TEST_DIR = $(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD = $(PYTHON) -m pytest
COMPONENT_TEST_ARGS =

# Typical failures for test target:
#=========================== short test summary info ============================
#FAILED unittest_modutils.py::ModPathFromFileTest::test_import_symlink_with_source_outside_of_path
#============ 1 failed, 987 passed, 43 skipped, 10 xfailed in 17.15s ============

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-39
