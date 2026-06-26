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
#   $WS_TOOLS/python-integrate-project prettytable
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		prettytable
HUMAN_VERSION =			3.18.0
COMPONENT_SUMMARY =		A simple Python library for easily displaying tabular data in a visually appealing ASCII table format
COMPONENT_PROJECT_URL =		https://github.com/prettytable/prettytable
COMPONENT_ARCHIVE_HASH =	\
	sha256:439217116152244369caf3d9f1caf2f9fe29b03bd79e88d2928c8e718c95d680
COMPONENT_LICENSE =		BSD-3-Clause

# Python 3.9 is not supported by prettytable >= 3.17.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += library/python/wcwidth
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-lazy-fixtures
