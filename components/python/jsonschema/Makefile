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
HUMAN_VERSION =			4.18.6
COMPONENT_SUMMARY =		jsonschema - An implementation of JSON Schema validation for Python
COMPONENT_PROJECT_URL =		https://github.com/python-jsonschema/jsonschema
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ae/a9/30605c5fe91e5087dacd85809322021106920a866d114a14f042781ffa3e/jsonschema-4.18.6.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:ce71d2f8c7983ef75a756e568317bf54bc531dc3ad7e66a128eae0d51623d8a3
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
