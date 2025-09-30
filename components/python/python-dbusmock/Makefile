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
#   $WS_TOOLS/python-integrate-project -d python/python-dbusmock python_dbusmock
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		python_dbusmock
HUMAN_VERSION =			0.37.0
COMPONENT_SUMMARY =		Mock D-Bus objects
COMPONENT_PROJECT_URL =		https://github.com/martinpitt/python-dbusmock
COMPONENT_ARCHIVE_HASH =	\
	sha256:38754c5ad2ad8f3936ff67d4b058bca416588a72bc094e91ded9f8f401b06310
COMPONENT_LICENSE =		LGPL-3.0-only
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# https://github.com/martinpitt/python-dbusmock/issues/247
PYTEST_ADDOPTS += --deselect tests/test_code.py::StaticCodeTests::test_black
# https://github.com/martinpitt/python-dbusmock/issues/246
PYTEST_ADDOPTS += --deselect tests/test_code.py::StaticCodeTests::test_pylint

# Manually added test dependencies
TEST_REQUIRED_PACKAGES += system/library/dbus

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/dbus-python
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += runtime/python
