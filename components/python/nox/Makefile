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
#   $WS_TOOLS/python-integrate-project nox
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		nox
HUMAN_VERSION =			2025.2.9
COMPONENT_SUMMARY =		Flexible test automation.
COMPONENT_ARCHIVE_HASH =	\
	sha256:d50cd4ca568bd7621c2e6cbbc4845b3b7f7697f25d5fb0190ce8f4600be79768
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_PEP735 += test

# https://github.com/wntrblm/nox/issues/926
PYTEST_ADDOPTS += --deselect tests/test_main.py::test_main_requires
PYTEST_ADDOPTS += --deselect tests/test_main.py::test_noxfile_script_mode

# Drop lines with timestamp
COMPONENT_TEST_TRANSFORMS += "-e '/nox >/d'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/argcomplete
PYTHON_REQUIRED_PACKAGES += library/python/attrs
PYTHON_REQUIRED_PACKAGES += library/python/colorlog
PYTHON_REQUIRED_PACKAGES += library/python/dependency-groups
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/virtualenv
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/tomli
