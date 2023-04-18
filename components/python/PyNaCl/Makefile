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
#   $WS_TOOLS/python-integrate-project PyNaCl
#

BUILD_STYLE = pyproject
PYTHON3_SOABI = abi3

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		PyNaCl
HUMAN_VERSION =			1.5.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		PyNaCl - Python binding to the Networking and Cryptography (NaCl) library
COMPONENT_PROJECT_URL =		https://github.com/pyca/pynacl/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/a7/22/27582568be639dfe22ddb3902225f91f2f17ceff88ce80e4db396c8986da/PyNaCl-1.5.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:8ac7448f09ab85811607bdd21ec2464495ac8b7c66d146bf545b0f08fb9220ba
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Use system libsodium
PYTHON_ENV += SODIUM_INSTALL=system

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cffi
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/pretend
TEST_REQUIRED_PACKAGES.python += library/python/pytest
