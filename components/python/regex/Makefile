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
HUMAN_VERSION =			2026.11.15
COMPONENT_SUMMARY =		Alternative regular expression module, to replace re.
COMPONENT_PROJECT_URL =		https://github.com/mrabarnett/mrab-regex
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/cf/e7/67c67920a3b5183388e0853a0a564a4bf60f2dd190a4e7626f5dad2fed62/regex-2026.11.15.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:d6ec7e29e62ebf93ab2a593d1137022b6025497d8610e5cb666d52f9ee5bb0ce
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
