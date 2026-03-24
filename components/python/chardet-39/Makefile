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
#   $WS_TOOLS/python-integrate-project -d python/chardet-39 chardet
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		chardet
HUMAN_VERSION =			5.2.0
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Universal encoding detector for Python 3
COMPONENT_PROJECT_URL =		http://chardet.github.io
COMPONENT_ARCHIVE_HASH =	\
	sha256:1b3b6ff479a8c414bc3fa2c0852995695c4a026dcd6d0633b2dd092ca39c1cf7
COMPONENT_LICENSE =		LGPL-2.1-only
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# chardet >= 6.0.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Test results order varies between runs
PYTEST_SORT_TESTS = yes

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
