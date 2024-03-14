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
HUMAN_VERSION =			13.0
COMPONENT_SUMMARY =		pytest-rerunfailures - pytest plugin to re-run tests to eliminate flaky failures
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-rerunfailures
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/41/40/26684be329d127f0402144b731dea116e8bce27d0b04cd91e8e0bea4df4a/pytest-rerunfailures-13.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:e132dbe420bc476f544b96e7036edd0a69707574209b6677263c950d19b09199
COMPONENT_LICENSE =		MPL-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# https://github.com/pytest-dev/pluggy/issues/457
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-checkdocs
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-console-scripts
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-enabler
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-relaxed
TEST_CONFLICTING_PACKAGES.python += library/python/typeguard
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
