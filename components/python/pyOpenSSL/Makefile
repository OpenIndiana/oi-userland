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
#   $WS_TOOLS/python-integrate-project pyOpenSSL
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyOpenSSL
HUMAN_VERSION =			23.2.0
COMPONENT_SUMMARY =		pyOpenSSL - Python wrapper module around the OpenSSL library
COMPONENT_PROJECT_URL =		https://pyopenssl.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/be/df/75a6525d8988a89aed2393347e9db27a56cb38a3e864314fac223e905aef/pyOpenSSL-23.2.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:276f931f55a452e7dea69c7173e984eb2a4407ce413c918aa34b55f82f9b8bac
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cryptography
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/flaky
TEST_REQUIRED_PACKAGES.python += library/python/pretend
TEST_REQUIRED_PACKAGES.python += library/python/pytest
