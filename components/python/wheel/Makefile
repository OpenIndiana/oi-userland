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
#   $WS_TOOLS/python-integrate-project wheel
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		wheel
HUMAN_VERSION =			0.45.1
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		A built-package format for Python
COMPONENT_ARCHIVE_HASH =	\
	sha256:661e1abd9198507b1409a20c02106d9670b2576e916d58f520316666abca6729
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - cachetools (test bootstrap)
# - chardet (test bootstrap)
# - distlib (test bootstrap)
# - tox-current-env (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

# Version 0.46.1 was yanked but we had it packaged.
COMPONENT_VERSION =		0.46.1

include $(WS_MAKE_RULES)/common.mk

# https://github.com/pypa/wheel/issues/658
PYTEST_ADDOPTS += --deselect tests/test_bdist_wheel.py::test_licenses_default
PYTEST_ADDOPTS += --deselect tests/test_bdist_wheel.py::test_licenses_deprecated
PYTEST_ADDOPTS += --deselect tests/test_bdist_wheel.py::test_licenses_override

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
