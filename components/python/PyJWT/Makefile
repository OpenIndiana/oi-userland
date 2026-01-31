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
#   $WS_TOOLS/python-integrate-project -d python/PyJWT pyjwt
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyjwt
HUMAN_VERSION =			2.11.0
COMPONENT_SUMMARY =		JSON Web Token implementation in Python
COMPONENT_PROJECT_URL =		https://github.com/jpadilla/pyjwt
COMPONENT_ARCHIVE_HASH =	\
	sha256:35f95c1f0fbe5d5ba6e43f00271c275f7a1a4db1dab27bf708073b75318ea623
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# This optional test dependency is needed to get consistent test results
TEST_REQUIRED_PACKAGES.python += library/python/cryptography

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
