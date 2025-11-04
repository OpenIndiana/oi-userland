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
#   $WS_TOOLS/python-integrate-project yamlfix
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		yamlfix
HUMAN_VERSION =			1.19.0
COMPONENT_SUMMARY =		A simple opionated yaml formatter that keeps your comments!
COMPONENT_PROJECT_URL =		https://github.com/lyz-code/yamlfix
COMPONENT_ARCHIVE_HASH =	\
	sha256:22f95ed2a5b88f46f06cf7922c616b6706d3596f23a0553138796ab909e5fa96
COMPONENT_LICENSE =		GPL-3.0-only
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

include $(WS_MAKE_RULES)/common.mk

# This project uses pdm to manage test dependencies.
TEST_REQUIREMENTS_PDM += test

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/click
REQUIRED_PACKAGES.python += library/python/maison
REQUIRED_PACKAGES.python += library/python/pdm-backend
REQUIRED_PACKAGES.python += library/python/pydantic
REQUIRED_PACKAGES.python += library/python/ruyaml
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
