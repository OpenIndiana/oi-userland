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
#   $WS_TOOLS/python-integrate-project dist-meta
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		dist-meta
HUMAN_VERSION =			0.8.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Parse and create Python distribution metadata.
COMPONENT_PROJECT_URL =		https://github.com/repo-helper/dist-meta
COMPONENT_ARCHIVE_URL =		\
	https://github.com/repo-helper/dist-meta/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:8491c92b85e80c844550f2081a08c0469bdd4fd61802c13c1c6afdcd16f8cbef
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# dist-meta --> shippinglabel ==> dist-meta
# dist-meta --> coincidence ==> whey ==> dist-meta
#
# To break loops we need to allow this component to integrate without testing in
# a case the required packages are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# https://github.com/repo-helper/dist-meta/issues/21#issuecomment-1464061088
PYTEST_ADDOPTS += --deselect tests/test_distributions.py::test_packages_distributions

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/domdf-python-tools
PYTHON_REQUIRED_PACKAGES += library/python/handy-archives
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/apeye
TEST_REQUIRED_PACKAGES.python += library/python/atomicwrites
TEST_REQUIRED_PACKAGES.python += library/python/attrs
TEST_REQUIRED_PACKAGES.python += library/python/coincidence
TEST_REQUIRED_PACKAGES.python += library/python/colorama
TEST_REQUIRED_PACKAGES.python += library/python/consolekit
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/first
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/importlib-metadata
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pypi-json
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-randomly
TEST_REQUIRED_PACKAGES.python += library/python/pytest-rerunfailures
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/pytz
TEST_REQUIRED_PACKAGES.python += library/python/shippinglabel
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
