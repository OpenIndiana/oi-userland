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
HUMAN_VERSION =			41.0.7
COMPONENT_SUMMARY =		cryptography - cryptography is a package which provides cryptographic recipes and primitives to Python developers.
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ce/b3/13a12ea7edb068de0f62bac88a8ffd92cc2901881b391839851846b84a81/cryptography-41.0.7.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:13f93ce9bea8016c253b34afc6bd6a75993e5c40672ed5405a9c832f0d4a00bc
COMPONENT_LICENSE =		Apache-2.0 OR BSD-3-Clause

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# https://www.illumos.org/issues/15767
LD_Z_IGNORE=

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += test

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
TEST_REQUIRED_PACKAGES.python += library/python/pretend
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-benchmark
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
