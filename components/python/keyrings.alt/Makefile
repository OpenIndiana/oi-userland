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
#   $WS_TOOLS/python-integrate-project -d python/keyrings.alt keyrings_alt
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		keyrings_alt
HUMAN_VERSION =			5.0.2
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Alternate keyring implementations
COMPONENT_ARCHIVE_HASH =	\
	sha256:8f097ebe9dc8b185106502b8cdb066c926d2180e13b4689fd4771a3eab7d69fb
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/jaraco-classes
REQUIRED_PACKAGES.python += library/python/jaraco-context
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/keyring
TEST_REQUIRED_PACKAGES.python += library/python/pycryptodome
TEST_REQUIRED_PACKAGES.python += library/python/pycryptodomex
TEST_REQUIRED_PACKAGES.python += library/python/pytest
