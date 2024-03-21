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
#   $WS_TOOLS/python-integrate-project graphviz
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		graphviz
HUMAN_VERSION =			0.20.3
COMPONENT_SUMMARY =		graphviz - Simple Python interface for Graphviz
COMPONENT_PROJECT_URL =		https://github.com/xflr6/graphviz
COMPONENT_ARCHIVE_HASH =	\
	sha256:09d6bc81e6a9fa392e7ba52135a9d49f1ed62526f96499325930e87ca1b5925d
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

COMPONENT_ARCHIVE =		$(COMPONENT_SRC).zip

include $(WS_MAKE_RULES)/common.mk

# https://github.com/pytest-dev/pytest/issues/12123
PYTEST_ADDOPTS += --ignore tests/backend/conftest.py
PYTEST_ADDOPTS += --ignore tests/conftest.py

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
