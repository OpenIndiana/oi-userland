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
HUMAN_VERSION =			4.19.0
COMPONENT_SUMMARY =		jsonschema - An implementation of JSON Schema validation for Python
COMPONENT_PROJECT_URL =		https://github.com/python-jsonschema/jsonschema
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/99/ba/e51d376c6160d27669c7a9ad0b61d9cbd58fa58be6e6ddc0e7e0b6e6aa40/jsonschema-4.19.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:6e1e7569ac13be8139b2dd2c21a55d350066ee3f80df06c608b398cdc6f30e8f
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy
PYTEST_ADDOPTS += -p no:randomly

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/attrs
PYTHON_REQUIRED_PACKAGES += library/python/hatch-fancy-pypi-readme
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/jsonschema-specifications
PYTHON_REQUIRED_PACKAGES += library/python/referencing
PYTHON_REQUIRED_PACKAGES += library/python/rpds-py
PYTHON_REQUIRED_PACKAGES += runtime/python
