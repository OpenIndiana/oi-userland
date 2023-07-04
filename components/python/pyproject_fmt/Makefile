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
#   $WS_TOOLS/python-integrate-project pyproject_fmt
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyproject_fmt
HUMAN_VERSION =			0.13.0
COMPONENT_SUMMARY =		pyproject_fmt - Format your pyproject.toml file
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ac/e3/687c38cda9efe4b7ab4b92975274ba2c33e0b33a6f5eff54548c96d26e4c/pyproject_fmt-0.13.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:aaad7398fe810c9087b33c1cc74d49b51a746bb05e9999371719b577139d0c49
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Turn off coverage because we are not interested in it and it could cause
# problems
COMPONENT_TEST_TARGETS += -- tests

# black makes test results not reproducible
PYTEST_ADDOPTS += -p no:black

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/natsort
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/tomlkit
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/covdefaults
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
