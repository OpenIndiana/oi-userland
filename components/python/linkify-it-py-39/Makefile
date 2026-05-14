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
#   $WS_TOOLS/python-integrate-project -d python/linkify-it-py-39 linkify-it-py
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		linkify-it-py
HUMAN_VERSION =			2.0.3
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Links recognition library with FULL unicode support.
COMPONENT_PROJECT_URL =		https://github.com/tsutsu3/linkify-it-py
COMPONENT_ARCHIVE_HASH =	\
	sha256:68cda27e162e9215c17d786649d1da0021a451bdc436ef9e0fa0ba5234b9b048
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# linkify-it-py >= 2.1.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Test results order varies between runs
PYTEST_SORT_TESTS = yes

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/uc-micro-py
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
