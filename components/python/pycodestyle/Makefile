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
#   $WS_TOOLS/python-integrate-project pycodestyle
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pycodestyle
HUMAN_VERSION =			2.15.0
COMPONENT_SUMMARY =		Python style guide checker
COMPONENT_PROJECT_URL =		https://pycodestyle.pycqa.org/
COMPONENT_ARCHIVE_URL =		\
	https://github.com/PyCQA/pycodestyle/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:3cb6afba1667f13b4ca7884154299108ef8e633a36526e29412a5cec7b5db4bd
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Python 3.9 is not supported by pycodestyle >= 2.15.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
