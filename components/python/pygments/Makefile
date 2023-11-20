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
#   $WS_TOOLS/python-integrate-project pygments
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pygments
HUMAN_VERSION =			2.17.1
COMPONENT_SUMMARY =		pygments - Pygments is a syntax highlighting package written in Python.
COMPONENT_PROJECT_URL =		https://pygments.org
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/22/04/097cdb7d5c6faee58e31a8a2b63cba2222a52066f734b3fdc713c6f40575/pygments-2.17.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:e45a0e74bf9c530f564ca81b8952343be986a29f6afe7f5ad95c5f06b7bdf5e8
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-randomly
TEST_REQUIRED_PACKAGES.python += library/python/wcag-contrast-ratio
