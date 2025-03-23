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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		decorator
HUMAN_VERSION =			5.2.1
COMPONENT_SUMMARY =		Decorators for Humans
COMPONENT_ARCHIVE_HASH =	\
	sha256:65f266143752f734b0a7cc83c46f4618af75b8c5911b00ccb61d0ac9b6da0360
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE.txt

# This project uses custom testing.  See $(SOURCE_DIR)/README.rst.
TEST_STYLE = custom

include $(WS_MAKE_RULES)/common.mk

# Custom testing
COMPONENT_TEST_CMD = $(PYTHON) tests/test.py
COMPONENT_TEST_ARGS = -v
COMPONENT_TEST_TARGETS =

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
