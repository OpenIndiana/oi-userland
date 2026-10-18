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
#   $WS_TOOLS/python-integrate-project -d python/validators-39 validators
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		validators
HUMAN_VERSION =			0.35.0
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Python Data Validation for Humans™
COMPONENT_PROJECT_URL =		https://python-validators.github.io/validators
COMPONENT_ARCHIVE_HASH =	\
	sha256:992d6c48a4e77c81f1b4daba10d16c3a9bb0dbb79b3a19ea847ff0928e70497a
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

# validators >= 0.36.0 requires Python >= 3.11
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# We do not have eth-hash packaged yet.
PYTEST_ADDOPTS += --ignore tests/crypto_addresses/test_eth_address.py
PYTEST_ADDOPTS += --ignore src/validators/crypto_addresses/eth_address.py

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
