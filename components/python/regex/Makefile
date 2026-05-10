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
#   $WS_TOOLS/python-integrate-project regex
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		regex
HUMAN_VERSION =			2026.5.9
COMPONENT_SUMMARY =		Alternative regular expression module, to replace re.
COMPONENT_PROJECT_URL =		https://github.com/mrabarnett/mrab-regex
COMPONENT_ARCHIVE_HASH =	\
	sha256:a8234aa23ec39894bfe4a3f1b85616a7032481964a13ac6fc9f10de4f6fca270
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

# Python 3.9 is not supported by regex >= 2026.2.19
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# https://github.com/mrabarnett/mrab-regex/issues/448#issuecomment-2222396902
PYTEST_ADDOPTS += --deselect regex/tests/test_regex.py::test_main

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
