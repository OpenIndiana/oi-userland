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
#   $WS_TOOLS/python-integrate-project -d python/pytest-39 pytest
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest
HUMAN_VERSION =			8.4.2
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		pytest: simple powerful testing with Python
COMPONENT_PROJECT_URL =		https://docs.pytest.org/en/latest/
COMPONENT_ARCHIVE_HASH =	\
	sha256:86c0d0b93306b961d58d62a4db4879f27fe25513d4b969df351abdddb3c30e01
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# pytest >= 9.0.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Workaround to run pytest indirectly (see tox.ini).
#
# This is needed because tox is unable to find pytest in proto area due to the
# following bug in tox-current-env:
# https://github.com/fedora-python/tox-current-env/issues/68
COMPONENT_TEST_ENV += _PYTEST_TOX_COVERAGE_RUN="python -m"

# This is needed to get consistent test results.
# See also https://github.com/pytest-dev/pytest/issues/11761
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/exceptiongroup
REQUIRED_PACKAGES.python += library/python/iniconfig
REQUIRED_PACKAGES.python += library/python/packaging
REQUIRED_PACKAGES.python += library/python/pluggy
REQUIRED_PACKAGES.python += library/python/pygments
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += library/python/tomli
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/argcomplete
TEST_REQUIRED_PACKAGES.python += library/python/attrs
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/mock
TEST_REQUIRED_PACKAGES.python += library/python/requests
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/xmlschema
