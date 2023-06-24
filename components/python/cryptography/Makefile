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
USE_COMMON_TEST_MASTER = no
PYTHON3_SOABI = abi3

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cryptography
HUMAN_VERSION =			38.0.4
COMPONENT_SUMMARY =		cryptography - cryptography is a package which provides cryptographic recipes and primitives to Python developers.
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/e3/3f/41186b1f2fd86a542d399175f6b8e43f82cd4dfa51235a0b030a042b811a/cryptography-38.0.4.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:175c1a818b87c9ac80bb7377f5520b7f31b3ef2a0004e2420319beadedb67290
COMPONENT_LICENSE =		(Apache-2.0 OR BSD-3-Clause) AND PSF-2.0

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Make sure we compile and link with proper openssl version
CFLAGS += -I$(OPENSSL_INCDIR)
CFLAGS += -L$(OPENSSL_LIBDIR)

# https://www.illumos.org/issues/15767
LD_Z_IGNORE=

# https://github.com/pyca/cryptography/issues/9111
TEST_CONFLICTING_PACKAGES.python += library/python/coverage-enable-subprocess

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cffi
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-rust
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += system/library
