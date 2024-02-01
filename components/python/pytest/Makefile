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
#   $WS_TOOLS/python-integrate-project pytest
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest
HUMAN_VERSION =			8.0.0
COMPONENT_SUMMARY =		pytest - pytest: simple powerful testing with Python
COMPONENT_PROJECT_URL =		https://docs.pytest.org/en/latest/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/50/fd/af2d835eed57448960c4e7e9ab76ee42f24bcdd521e967191bc26fa2dece/pytest-8.0.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:249b1b0864530ba251b7438274c4d251c58d868edaaec8762893ad4a0d71c36c
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - Userland testing framework (see setup.py.mk)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Workaround to run pytest indirectly (see tox.ini).
#
# This is needed because tox is unable to find pytest in proto area due to the
# following bug in tox-current-env:
# https://github.com/fedora-python/tox-current-env/issues/68
COMPONENT_TEST_ENV += _PYTEST_TOX_COVERAGE_RUN="python -m"

# https://github.com/pytest-dev/pluggy/issues/457
# https://github.com/bitprophet/pytest-relaxed/issues/28
# https://github.com/christiansandberg/pytest-reporter/issues/8
# https://github.com/jaraco/pytest-enabler/issues/10
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-checkdocs
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-console-scripts
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-enabler
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-lazy-fixture
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-metadata
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-randomly
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-relaxed
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-reporter
TEST_CONFLICTING_PACKAGES.python += library/python/typeguard

# This is needed to get consistent test results.
# See also https://github.com/pytest-dev/pytest/issues/11761
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/exceptiongroup
PYTHON_REQUIRED_PACKAGES += library/python/iniconfig
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/pluggy
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/argcomplete
TEST_REQUIRED_PACKAGES.python += library/python/attrs
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/mock
TEST_REQUIRED_PACKAGES.python += library/python/nose
TEST_REQUIRED_PACKAGES.python += library/python/pygments
TEST_REQUIRED_PACKAGES.python += library/python/requests
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/xmlschema
