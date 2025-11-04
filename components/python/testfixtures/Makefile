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
#   $WS_TOOLS/python-integrate-project testfixtures
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		testfixtures
HUMAN_VERSION =			8.3.0
COMPONENT_SUMMARY =		A collection of helpers and mock objects for unit tests and doc tests.
COMPONENT_PROJECT_URL =		https://github.com/Simplistix/testfixtures
COMPONENT_ARCHIVE_HASH =	\
	sha256:d4c0b84af2f267610f908009b50d6f983a4e58ade22c67bab6787b5a402d59c0
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# We have no django packaged yet.
COMPONENT_POST_UNPACK_ACTION += $(RM) $(COMPONENT_SRC)/testfixtures/django.py ;
COMPONENT_POST_UNPACK_ACTION += $(RM) -r $(COMPONENT_SRC)/testfixtures/tests/test_django ;

# The pytest discovery finds tests in build/lib, but that does not work.
PYTEST_ADDOPTS += testfixtures

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += test

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/mypy
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/sybil
TEST_REQUIRED_PACKAGES.python += library/python/twisted
