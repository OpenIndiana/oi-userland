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
HUMAN_VERSION =			2.1.4
COMPONENT_SUMMARY =		pdm_backend - The build backend used by PDM that supports latest packaging standards
COMPONENT_PROJECT_URL =		https://github.com/pdm-project/pdm-backend
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/f9/bd/393be60c563dd0b25e341f6abef396309f6c12d2bfee4014e521f96b1286/pdm_backend-2.1.4.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f39637cafd739213459a41d27421bad8601eed5262ac828c2519b023a0ffbf14
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += runtime/python
