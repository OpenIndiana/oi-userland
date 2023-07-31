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
#   $WS_TOOLS/python-integrate-project nbformat
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		nbformat
HUMAN_VERSION =			5.9.2
COMPONENT_SUMMARY =		nbformat - The Jupyter Notebook format
COMPONENT_PROJECT_URL =		https://jupyter.org
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/54/d8/31dceef56952da6ea2c43405a83c9759a22a86cb530197988cfa8599b178/nbformat-5.9.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:5f98b5ba1997dff175e77e0c17d5c10a96eaed2cbd1de3533d1fc35d5e111192
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/fastjsonschema
PYTHON_REQUIRED_PACKAGES += library/python/hatch-nodejs-version
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/jsonschema
PYTHON_REQUIRED_PACKAGES += library/python/jupyter-core
PYTHON_REQUIRED_PACKAGES += library/python/traitlets
PYTHON_REQUIRED_PACKAGES += runtime/python
