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
#   $WS_TOOLS/python-integrate-project service_identity
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		service_identity
HUMAN_VERSION =			23.1.0
COMPONENT_SUMMARY =		service_identity - Service identity verification for pyOpenSSL & cryptography.
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/3b/98/2a46c7414ffc1d06ba67d2c2dd62a207a70cb351028a8cd8c85b3dbd1cf7/service_identity-23.1.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:ecb33cd96307755041e978ab14f8b14e13b40f1fbd525a4dc78f46d2b986431d
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# service-identity >= 23.1.0 requires Python >= 3.8
PYTHON_VERSIONS := $(filter-out 3.7, $(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/attrs
PYTHON_REQUIRED_PACKAGES += library/python/cryptography
PYTHON_REQUIRED_PACKAGES += library/python/hatch-fancy-pypi-readme
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/pyasn1
PYTHON_REQUIRED_PACKAGES += library/python/pyasn1-modules
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/pytest
