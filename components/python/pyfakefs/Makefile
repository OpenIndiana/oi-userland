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
HUMAN_VERSION =			6.2.0
COMPONENT_SUMMARY =		Implements a fake file system that mocks the Python file system modules.
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pyfakefs
COMPONENT_ARCHIVE_HASH =	\
	sha256:e59a36db447bf509ce9c97ab3d1510c08cc51895c5311325a560a5e5b5dc1940
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	COPYING

# Python 3.9 is not supported by pyfakefs >= 6.0.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# This is needed to avoid ImportPathMismatchError
COMPONENT_TEST_ENV += PYTHONPATH=$(COMPONENT_TEST_DIR):$(PROTOPYTHONVENDORDIR)

# Normalize pointers
COMPONENT_TEST_TRANSFORMS += "-e 's/0x[0-9a-f]\{12\}/\$$(POINTER)/g'"
# Random temporary file name
COMPONENT_TEST_TRANSFORMS += "-e 's|\(/tmp/tmp\).\{8\}|\1XXXXXXXX|'"
COMPONENT_TEST_TRANSFORMS += "-e 's/\(KeyError: '\"'\"'tmp\).\{8\}'\"'\"'/\1XXXXXXXX'\"'\"'/'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
