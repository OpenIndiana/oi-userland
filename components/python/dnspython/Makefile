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
#   $WS_TOOLS/python-integrate-project dnspython
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		dnspython
HUMAN_VERSION =			2.7.0
COMPONENT_SUMMARY =		DNS toolkit
COMPONENT_ARCHIVE_HASH =	\
	sha256:ce9c432eda0dc91cf618a5cedf1a4e142651196bbcd2c80e89ed5a907e5cfaf1
COMPONENT_LICENSE =		ISC
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# The following four tests needs OpenSSL >= 3.2 to pass
PYTEST_ADDOPTS += --deselect tests/test_dnssec.py::DNSSECSignatureTestCase::testDeterministicSignatureECDSAP256SHA256
PYTEST_ADDOPTS += --deselect tests/test_dnssec.py::DNSSECSignatureTestCase::testSignatureECDSAP256SHA256
PYTEST_ADDOPTS += --deselect tests/test_dnssec.py::DNSSECSignatureTestCase::testSignatureECDSAP384SHA384
PYTEST_ADDOPTS += --deselect tests/test_dnssecalgs.py::DNSSECAlgorithm::test_ecdsa

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += runtime/python
