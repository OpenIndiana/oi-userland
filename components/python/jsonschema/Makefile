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
#   $WS_TOOLS/python-integrate-project jsonschema
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		jsonschema
HUMAN_VERSION =			4.26.0
COMPONENT_SUMMARY =		An implementation of JSON Schema validation for Python
COMPONENT_PROJECT_URL =		https://github.com/python-jsonschema/jsonschema
COMPONENT_ARCHIVE_HASH =	\
	sha256:0c26707e2efad8aa1bfc5b7ce170f3fccc2e4918ff85989ba9ffa9facb2be326
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = pytest

# Python 3.9 is not supported by jsonschema >= 4.26.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_PEP735 += test

# We have no jsonpath-ng packaged (yet)
PYTEST_ADDOPTS += --ignore jsonschema/tests/test_exceptions.py

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/attrs
REQUIRED_PACKAGES.python += library/python/hatch-fancy-pypi-readme
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += library/python/jsonschema-specifications
REQUIRED_PACKAGES.python += library/python/referencing
REQUIRED_PACKAGES.python += library/python/rpds-py
REQUIRED_PACKAGES.python += runtime/python
