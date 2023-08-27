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
HUMAN_VERSION =			5.2.4
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		pyfakefs - pyfakefs implements a fake file system that mocks the Python file system modules.
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pyfakefs
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/2a/54/9eef50804852e60d0b7712e557e4e8a563a78cd42a6acde0c511253c5f02/pyfakefs-5.2.4.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:3e040f3792086086a0dc2191b05fe709438e168aafe2e94fcdbef8e3859208d8
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# The following test file requires OpenTimelineIO.
# We have no OpenTimelineIO packaged yet.
COMPONENT_POST_UNPACK_ACTION += \
	$(RM) $(SOURCE_DIR)/pyfakefs/pytest_tests/segfault_test.py ;

# https://github.com/pytest-dev/pyfakefs/issues/870
COMPONENT_TEST_ENV += HOME=/tmp

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
