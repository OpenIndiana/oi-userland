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
#   $WS_TOOLS/python-integrate-project service-identity
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		service-identity
HUMAN_VERSION =			21.1.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		service-identity - Service identity verification for pyOpenSSL & cryptography.
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/09/2e/26ade69944773df4748c19d3053e025b282f48de02aad84906d34a29d28b/service-identity-21.1.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:6e6c6086ca271dc11b033d17c3a8bea9f24ebff920c587da090afc9519419d34
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# service-identity >= 23.1.0 requires Python >= 3.8
PYTHON_VERSIONS = 3.7

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/attrs
PYTHON_REQUIRED_PACKAGES += library/python/cryptography
PYTHON_REQUIRED_PACKAGES += library/python/pyasn1
PYTHON_REQUIRED_PACKAGES += library/python/pyasn1-modules
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/six
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/pytest
