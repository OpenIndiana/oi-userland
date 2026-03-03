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
#   $WS_TOOLS/python-integrate-project imagesize
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		imagesize
HUMAN_VERSION =			1.5.0
COMPONENT_SUMMARY =		Getting image size from png/jpeg/jpeg2000/gif file
COMPONENT_PROJECT_URL =		https://github.com/shibukawa/imagesize_py
COMPONENT_ARCHIVE_HASH =	\
	sha256:8bfc5363a7f2133a89f0098451e0bcb1cd71aba4dc02bbcecb39d99d40e1b94f
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.rst

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# https://github.com/shibukawa/imagesize_py/issues/62
PYTEST_ADDOPTS += --deselect test/test_get_filelike.py::test_get_filelike

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
