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
#   $WS_TOOLS/python-integrate-project stestr
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		stestr
HUMAN_VERSION =			4.1.0
COMPONENT_SUMMARY =		stestr - A parallel Python test runner built around subunit
COMPONENT_PROJECT_URL =		http://stestr.readthedocs.io/en/latest/
COMPONENT_ARCHIVE_HASH =	\
	sha256:5f61c369eece63c292d13599e12aa158af7685990643f24dd6fa7fabfe34e98a
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# stestr is used to test stestr
USE_STESTR = yes

# Ignore stdout and stderr of successfull tests
TOX_POSARGS += --suppress-attachments

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cliff
PYTHON_REQUIRED_PACKAGES += library/python/extras
PYTHON_REQUIRED_PACKAGES += library/python/fixtures
PYTHON_REQUIRED_PACKAGES += library/python/pbr
PYTHON_REQUIRED_PACKAGES += library/python/python-subunit
PYTHON_REQUIRED_PACKAGES += library/python/pyyaml
PYTHON_REQUIRED_PACKAGES += library/python/testtools
PYTHON_REQUIRED_PACKAGES += library/python/tomlkit
PYTHON_REQUIRED_PACKAGES += library/python/voluptuous
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/black
TEST_REQUIRED_PACKAGES.python += library/python/cliff
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/ddt
TEST_REQUIRED_PACKAGES.python += library/python/extras
TEST_REQUIRED_PACKAGES.python += library/python/fixtures
TEST_REQUIRED_PACKAGES.python += library/python/iso8601
TEST_REQUIRED_PACKAGES.python += library/python/pbr
TEST_REQUIRED_PACKAGES.python += library/python/python-subunit
TEST_REQUIRED_PACKAGES.python += library/python/pyyaml
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/testtools
TEST_REQUIRED_PACKAGES.python += library/python/tomlkit
TEST_REQUIRED_PACKAGES.python += library/python/voluptuous
