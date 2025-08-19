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
HUMAN_VERSION =			4.25.1
COMPONENT_SUMMARY =		An implementation of JSON Schema validation for Python
COMPONENT_PROJECT_URL =		https://github.com/python-jsonschema/jsonschema
COMPONENT_ARCHIVE_HASH =	\
	sha256:e4a9655ce0da0c0b67a085847e00a3a51449e1157f4f75e9fb5aa545e122eb85
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_PEP735 += test

# We have no jsonpath-ng packaged (yet)
PYTEST_ADDOPTS += --ignore jsonschema/tests/test_exceptions.py

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/attrs
PYTHON_REQUIRED_PACKAGES += library/python/hatch-fancy-pypi-readme
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/jsonschema-specifications
PYTHON_REQUIRED_PACKAGES += library/python/referencing
PYTHON_REQUIRED_PACKAGES += library/python/rpds-py
PYTHON_REQUIRED_PACKAGES += runtime/python
