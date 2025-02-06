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
#   $WS_TOOLS/python-integrate-project pyfakefs
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyfakefs
HUMAN_VERSION =			5.7.4
COMPONENT_SUMMARY =		pyfakefs implements a fake file system that mocks the Python file system modules.
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pyfakefs
COMPONENT_ARCHIVE_HASH =	\
	sha256:4971e65cc80a93a1e6f1e3a4654909c0c493186539084dc9301da3d68c8878fe
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	COPYING

include $(WS_MAKE_RULES)/common.mk

# Normalize pointers
COMPONENT_TEST_TRANSFORMS += "-e 's/0x[0-9a-f]\{12\}/\$$(POINTER)/g'"
# Random temporary file name
COMPONENT_TEST_TRANSFORMS += "-e 's|\(/tmp/tmp\).\{8\}|\1XXXXXXXX|'"
COMPONENT_TEST_TRANSFORMS += "-e 's/\(KeyError: '\"'\"'tmp\).\{8\}'\"'\"'/\1XXXXXXXX'\"'\"'/'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
