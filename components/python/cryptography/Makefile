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
CARGO_VENDOR = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cryptography
HUMAN_VERSION =			48.0.0
COMPONENT_SUMMARY =		cryptography is a package which provides cryptographic recipes and primitives to Python developers.
COMPONENT_PROJECT_URL =		https://github.com/pyca/cryptography
COMPONENT_ARCHIVE_HASH =	\
	sha256:5c3932f4436d1cccb036cb0eaef46e6e2db91035166f1ad6505c3c9d5a635920
COMPONENT_LICENSE =		Apache-2.0 OR BSD-3-Clause

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_PEP735 += test

# https://github.com/pyca/cryptography/issues/9111
TEST_CONFLICTING_PACKAGES.python += library/python/coverage-enable-subprocess

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/cffi
REQUIRED_PACKAGES.python += library/python/maturin
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/typing-extensions
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/certifi
TEST_REQUIRED_PACKAGES.python += library/python/cryptography-vectors
TEST_REQUIRED_PACKAGES.python += library/python/pretend
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-benchmark
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
