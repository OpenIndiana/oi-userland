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
#   $WS_TOOLS/python-integrate-project tempora
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		tempora
HUMAN_VERSION =			5.2.2
COMPONENT_SUMMARY =		tempora - Objects and routines pertaining to date and time (tempora)
COMPONENT_PROJECT_URL =		https://github.com/jaraco/tempora
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/1c/32/963e37d9ad64582b822b8bf3288ac135ede936e5c8fe1c71da74164f0974/tempora-5.2.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:98ee27bc528c91a236f9a5d612ede4ef391b01f7862bf11b483ce549053651c1
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# https://github.com/tholo/pytest-flake8/issues/92
PYTEST_ADDOPTS += -p no:flake8

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-functools
PYTHON_REQUIRED_PACKAGES += library/python/pytz
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/backports-unittest-mock
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/freezegun
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-black
TEST_REQUIRED_PACKAGES.python += library/python/pytest-checkdocs
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-enabler
TEST_REQUIRED_PACKAGES.python += library/python/pytest-flake8
TEST_REQUIRED_PACKAGES.python += library/python/pytest-freezegun
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
TEST_REQUIRED_PACKAGES.python += library/python/types-freezegun
TEST_REQUIRED_PACKAGES.python += library/python/types-pytz
