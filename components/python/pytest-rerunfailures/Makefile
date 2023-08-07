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
HUMAN_VERSION =			12.0
COMPONENT_SUMMARY =		pytest-rerunfailures - pytest plugin to re-run tests to eliminate flaky failures
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-rerunfailures
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/97/66/40f778791860c5234c5c677026d45c1a8708873b3dba8111de672bceac4f/pytest-rerunfailures-12.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:784f462fa87fe9bdf781d0027d856b47a4bfe6c12af108f6bd887057a917b48e
COMPONENT_LICENSE =		MPL-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Testing fails with the following packages installed
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-black
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-mypy
# https://github.com/pytest-dev/pytest-rerunfailures/issues/218
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-randomly
# https://github.com/pytest-dev/pytest-rerunfailures/issues/217
TEST_CONFLICTING_PACKAGES.python += library/python/flaky

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
