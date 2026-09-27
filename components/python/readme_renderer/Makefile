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
#   $WS_TOOLS/python-integrate-project readme_renderer
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		readme_renderer
HUMAN_VERSION =			46.0
COMPONENT_SUMMARY =		readme_renderer is a library for rendering readme descriptions for Warehouse
COMPONENT_PROJECT_URL =		https://github.com/pypa/readme_renderer
COMPONENT_ARCHIVE_HASH =	\
	sha256:af3e964914f6310a33ff67b72a4bdd940bed8d7c3bdecd2d14f40edf284bfe90
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# Python 3.9 is not supported by readme-renderer >= 45.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Test results order varies between runs
PYTEST_SORT_TESTS = yes

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/docutils
REQUIRED_PACKAGES.python += library/python/nh3
REQUIRED_PACKAGES.python += library/python/pygments
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
