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
#   $WS_TOOLS/python-integrate-project pytest-rerunfailures
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest-rerunfailures
HUMAN_VERSION =			11.1.2
COMPONENT_SUMMARY =		pytest-rerunfailures - pytest plugin to re-run tests to eliminate flaky failures
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-rerunfailures
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/08/31/fb028a35b1d21086a4bea33a3b4b1f90304e5150d33c8d70a42fd10e4aff/pytest-rerunfailures-11.1.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:55611661e873f1cafa384c82f08d07883954f4b76435f4b8a5b470c1954573de
COMPONENT_LICENSE =		MPL-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

#
# Testing of pytest-rerunfailures fails if there is flaky installed.  See
# https://github.com/pytest-dev/pytest-rerunfailures/issues/217 for details.
#
# Testing of pytest-rerunfailures fails if there is pytest-randomly installed.
# See https://github.com/pytest-dev/pytest-rerunfailures/issues/218 for
# details.
#
# To see pytest-rerunfailures tests to pass both flaky and pytest-randomly
# packages should NOT be installed during testing.
#

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
