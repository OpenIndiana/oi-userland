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
#   $WS_TOOLS/python-integrate-project -d python/PyNaCl pynacl
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pynacl
HUMAN_VERSION =			1.6.2
COMPONENT_SUMMARY =		Python binding to the Networking and Cryptography (NaCl) library
COMPONENT_PROJECT_URL =		https://github.com/pyca/pynacl/
COMPONENT_ARCHIVE_HASH =	\
	sha256:018494d6d696ae03c7e656e5e74cdfd8ea1326962cc401bcf018f1ed8436811c
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Use system libsodium
PYTHON_ENV += SODIUM_INSTALL=system

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += tests

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/cffi
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
