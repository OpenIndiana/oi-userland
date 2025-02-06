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
#   $WS_TOOLS/python-integrate-project validators
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		validators
HUMAN_VERSION =			0.34.0
COMPONENT_SUMMARY =		Python Data Validation for Humans™
COMPONENT_PROJECT_URL =		https://python-validators.github.io/validators
COMPONENT_ARCHIVE_HASH =	\
	sha256:647fe407b45af9a74d245b943b18e6a816acf4926974278f6dd617778e1e781f
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# We do not have eth-hash packaged yet.
PYTEST_ADDOPTS += --ignore tests/crypto_addresses/test_eth_address.py

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
