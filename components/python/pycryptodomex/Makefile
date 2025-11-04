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
#   $WS_TOOLS/python-integrate-project pycryptodomex
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pycryptodomex
HUMAN_VERSION =			3.23.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Cryptographic library for Python
COMPONENT_PROJECT_URL =		https://www.pycryptodome.org
COMPONENT_ARCHIVE_HASH =	\
	sha256:71909758f010c82bc99b0abf4ea12012c98962fbf0583c2164f8b84533c2e4da
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE.rst

# https://github.com/Legrandin/pycryptodome/issues/731
TEST_STYLE = setup.py

include $(WS_MAKE_RULES)/common.mk

# get verbose test output
COMPONENT_TEST_TARGETS += -vv

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += requirements-test.txt

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pycryptodome-test-vectors
