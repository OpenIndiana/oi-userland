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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		astroid
COMPONENT_VERSION=	1.4.8
COMPONENT_PROJECT_URL=	http://bitbucket.org/logilab/$(COMPONENT_NAME)
COMPONENT_ARCHIVE_HASH=	\
	sha256:5f064785a7e45ed519285f2eb30b795e58a4932a0736b32030da6fef3394ddb3
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_BUGDB=	python-mod/astroid

TPNO=			31346

BUILD_STYLE= setup.py
SYSTEM_TEST_TARGET= $(SYSTEM_TEST_NO_ARCH)
include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_ENV = PYTHONPATH=$(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES)

COMPONENT_TEST_DIR = $(COMPONENT_SRC)/astroid/tests
COMPONENT_TEST_CMD = /usr/bin/pytest-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =

# The test output contains details from each test, in whatever order they
# complete. Use nawk to extract just the sections that summarizes the test
# result.
COMPONENT_TEST_TRANSFORMER =	$(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/Ran (.+) test cases/{ sub(/in(.+)\)/, \"\"); print }/All (.+) modules OK/'"


# This modutils test should expect the logilab module to be found under the
# standard /usr/lib/python* location when we test installed system bits,
# the opposite of what it expects when testing built bits in the proto area.
# Temporarily modify its expected result for system-test,
# and restore it afterwards.
COMPONENT_PRE_SYSTEM_TEST_ACTION += \
	($(MV) $(COMPONENT_SRC)/astroid/tests/unittest_modutils.py $(COMPONENT_SRC)/astroid/tests/unittest_modutils.py-orig; \
	$(GSED) -e "s/self.assertEqual(modutils.is_standard_module('logilab'), False)/self.assertEqual(modutils.is_standard_module('logilab'), True)/" $(COMPONENT_SRC)/astroid/tests/unittest_modutils.py-orig > $(COMPONENT_SRC)/astroid/tests/unittest_modutils.py)
COMPONENT_SYSTEM_TEST_DIR = $(COMPONENT_SRC)/astroid/tests
COMPONENT_SYSTEM_TEST_CMD = /usr/bin/pytest-$(PYTHON_VERSION)
COMPONENT_SYSTEM_TEST_ARGS =
COMPONENT_POST_SYSTEM_TEST_ACTION += \
	$(MV) $(COMPONENT_SRC)/astroid/tests/unittest_modutils.py-orig $(COMPONENT_SRC)/astroid/tests/unittest_modutils.py
