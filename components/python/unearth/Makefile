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
#   $WS_TOOLS/python-integrate-project unearth
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		unearth
HUMAN_VERSION =			0.14.0
COMPONENT_SUMMARY =		unearth - A utility to fetch and download python packages
COMPONENT_PROJECT_URL =		https://github.com/frostming/unearth
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/2c/8e/55f2075b91268108c97e025275dd6cf0c03ec648ba28834f9c79fbc64fe1/unearth-0.14.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f3cddfb94ac0f865fbcf964231556ef7183010379c00b01205517a50c78a186d
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIRED_PACKAGES.python += library/python/pytest-httpserver

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/pdm-backend
PYTHON_REQUIRED_PACKAGES += library/python/requests
PYTHON_REQUIRED_PACKAGES += runtime/python
