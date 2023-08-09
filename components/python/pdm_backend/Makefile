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
#   $WS_TOOLS/python-integrate-project pdm_backend
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pdm_backend
HUMAN_VERSION =			2.1.5
COMPONENT_SUMMARY =		pdm_backend - The build backend used by PDM that supports latest packaging standards
COMPONENT_PROJECT_URL =		https://github.com/pdm-project/pdm-backend
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/12/0d/cfe7ce34e411d44bd4e1863c8332365e8bfddedc84a0c51f18ab76ae4aec/pdm_backend-2.1.5.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:38ea0b3888293d99407928fe3ab841cca2785ce951decc7c96bfa9be7314f9ed
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += runtime/python
