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
#   $WS_TOOLS/python-integrate-project -d python/packageurl-python packageurl_python
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		packageurl_python
HUMAN_VERSION =			0.17.6
COMPONENT_SUMMARY =		A purl aka. Package URL parser and builder
COMPONENT_PROJECT_URL =		https://github.com/package-url/packageurl-python
COMPONENT_ARCHIVE_HASH =	\
	sha256:1252ce3a102372ca6f86eb968e16f9014c4ba511c5c37d95a7f023e2ca6e5c25
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	mit.LICENSE

TEST_STYLE = pytest

# We do not need packageurl-python for Python 3.9
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += test

# https://github.com/package-url/packageurl-python/issues/242
PYTEST_ADDOPTS += --ignore tests/test_purl_spec.py

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
