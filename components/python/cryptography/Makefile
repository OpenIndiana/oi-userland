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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cryptography
HUMAN_VERSION =			42.0.1
COMPONENT_SUMMARY =		cryptography - cryptography is a package which provides cryptographic recipes and primitives to Python developers.
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/3f/ed/a233522ab5201b988a482cbb19ae3b63bef8ad2ad3e11fc5216b7053b2e4/cryptography-42.0.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:fd33f53809bb363cf126bebe7a99d97735988d9b0131a2be59fbf83e1259a5b7
COMPONENT_LICENSE =		Apache-2.0 OR BSD-3-Clause

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# https://www.illumos.org/issues/15767
LD_Z_IGNORE=

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += test
# https://github.com/pyca/cryptography/issues/10242
TEST_REQUIRED_PACKAGES.python += library/python/cryptography-vectors

# https://github.com/pyca/cryptography/issues/9111
TEST_CONFLICTING_PACKAGES.python += library/python/coverage-enable-subprocess

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cffi
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-rust
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += library/security/openssl-31
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/certifi
TEST_REQUIRED_PACKAGES.python += library/python/pretend
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-benchmark
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
