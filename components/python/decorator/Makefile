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
# This file was automatically generated using the following command:
#   $WS_TOOLS/python-integrate-project decorator
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		decorator
HUMAN_VERSION =			5.3.2
COMPONENT_SUMMARY =		Decorators for Humans
COMPONENT_PROJECT_URL =		https://github.com/micheles/decorator
COMPONENT_ARCHIVE_HASH =	\
	sha256:d9883f1b8259e3bfc42565d0bc6fdc760012008552aa449f75efd2d48319b82b
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE.txt

# This project uses custom testing.  See $(SOURCE_DIR)/README.rst.
TEST_STYLE = custom

include $(WS_MAKE_RULES)/common.mk

# Testing needs to find the documentation module in the build directory
COMPONENT_TEST_ENV += PYTHONPATH=$(PROTOPYTHONVENDORDIR):$(COMPONENT_TEST_DIR)/tests

# Custom testing
COMPONENT_TEST_CMD = $(PYTHON) tests/test.py
COMPONENT_TEST_ARGS = -v
COMPONENT_TEST_TARGETS =

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
