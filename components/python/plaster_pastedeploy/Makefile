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
#   $WS_TOOLS/python-integrate-project plaster_pastedeploy
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		plaster_pastedeploy
HUMAN_VERSION =			1.0.1
COMPONENT_SUMMARY =		plaster_pastedeploy - A loader implementing the PasteDeploy syntax to be used by plaster.
COMPONENT_PROJECT_URL =		https://github.com/Pylons/plaster_pastedeploy
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/c7/af/01a22f73ce97c6375c88d7ceaf6f5f4f345e940da93c94f98833d898a449/plaster_pastedeploy-1.0.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:be262e6d2e41a7264875daa2fe2850cbb0615728bcdc92828fdc72736e381412
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pastedeploy
PYTHON_REQUIRED_PACKAGES += library/python/plaster
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
