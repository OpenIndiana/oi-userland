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
#   $WS_TOOLS/python-integrate-project executing
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		executing
HUMAN_VERSION =			2.2.1
COMPONENT_SUMMARY =		Get the currently executing AST node of a frame, and other information
COMPONENT_PROJECT_URL =		https://github.com/alexmojaki/executing
COMPONENT_ARCHIVE_HASH =	\
	sha256:3632cc370565f6648cc328b32435bd120a1e4ebb20c77e3fdde9a13cd1e533c4
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Test results order varies between runs
PYTEST_SORT_TESTS = yes

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/asttokens
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/coverage-enable-subprocess
TEST_REQUIRED_PACKAGES.python += library/python/ipython
TEST_REQUIRED_PACKAGES.python += library/python/littleutils
TEST_REQUIRED_PACKAGES.python += library/python/pytest
