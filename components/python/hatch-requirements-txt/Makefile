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
#   $WS_TOOLS/python-integrate-project hatch-requirements-txt
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		hatch-requirements-txt
HUMAN_VERSION =			0.4.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Hatchling plugin to read project dependencies from requirements.txt
COMPONENT_PROJECT_URL =		https://github.com/repo-helper/hatch-requirements-txt
COMPONENT_ARCHIVE_URL =		\
	https://github.com/repo-helper/hatch-requirements-txt/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:69383f2c2a72b68dff0ec564358280bed8e2a5e9971e9871b8ff4d7c978ec9f5
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# hatch-requirements-txt --> coincidence ==> whey ==> pyproject-parser ==> apeye-core ==> hatch-requirements-txt
#
# To break loops we need to allow this component to integrate without testing in
# a case the required packages are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# https://github.com/repo-helper/hatch-requirements-txt/issues/62
PYTEST_ADDOPTS += --deselect tests/test_errors.py::test_not_dynamic_but_filename_defined
PYTEST_ADDOPTS += --deselect tests/test_errors.py::test_not_dynamic_but_files_defined

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coincidence
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/dist-meta
TEST_REQUIRED_PACKAGES.python += library/python/domdf-python-tools
TEST_REQUIRED_PACKAGES.python += library/python/importlib-metadata
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pkginfo
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-randomly
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
