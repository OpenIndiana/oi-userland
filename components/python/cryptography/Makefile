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
#   $WS_TOOLS/python-integrate-project cryptography
#

BUILD_STYLE = pyproject
PYTHON3_SOABI = abi3

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cryptography
HUMAN_VERSION =			3.2.1
COMPONENT_SUMMARY =		cryptography - cryptography is a package which provides cryptographic recipes and primitives to Python developers.
COMPONENT_PROJECT_URL =		https://github.com/pyca/cryptography
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/94/5c/42de91c7fbdb817b2d9a4e64b067946eb38a4eb36c1a09c96c87a0f86a82/cryptography-3.2.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:d3d5e10be0cf2a12214ddee45c6bd203dab435e3d83b4560c03066eda600bfe3
COMPONENT_LICENSE =		(Apache-2.0 OR BSD-3-Clause) AND PSF-2.0

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cffi
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/six
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
