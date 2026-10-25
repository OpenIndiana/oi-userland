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
#   $WS_TOOLS/python-integrate-project asgiref
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		asgiref
HUMAN_VERSION =			3.13.0
COMPONENT_SUMMARY =		ASGI specs, helper code, and adapters
COMPONENT_PROJECT_URL =		https://github.com/django/asgiref/
COMPONENT_ARCHIVE_HASH =	\
	sha256:034cc8cbf72d00553b4be256703ac545120b4e50af13b49dec99da899aeeecb4
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

# Python 3.9 is not supported by asgiref >= 3.12.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# https://github.com/django/asgiref/issues/450
COMPONENT_TEST_TRANSFORMS += "-e '/^task: /d'"

# https://github.com/django/asgiref/issues/607
PYTEST_ADDOPTS += --ignore tests/test_benchmark_local.py

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-asyncio
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
