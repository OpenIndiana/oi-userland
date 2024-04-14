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
#   $WS_TOOLS/python-integrate-project Faker
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Faker
HUMAN_VERSION =			24.9.0
COMPONENT_SUMMARY =		Faker - Faker is a Python package that generates fake data for you.
COMPONENT_PROJECT_URL =		https://github.com/joke2k/faker
COMPONENT_ARCHIVE_HASH =	\
	sha256:73b1e7967b0ceeac42fc99a8c973bb49e4499cc4044d20d17ab661d5cb7eda1d
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# https://github.com/pytest-dev/pytest/issues/12186
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-black
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-mypy
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-salt-factories
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-system-statistics

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/python-dateutil
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/freezegun
TEST_REQUIRED_PACKAGES.python += library/python/pillow
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/ukpostcodeparser
TEST_REQUIRED_PACKAGES.python += library/python/validators
TEST_REQUIRED_PACKAGES.python += library/python/xmltodict
