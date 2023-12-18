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
#   $WS_TOOLS/python-integrate-project psutil
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		psutil
HUMAN_VERSION =			5.9.7
COMPONENT_SUMMARY =		psutil - Cross-platform lib for process and system monitoring in Python.
COMPONENT_PROJECT_URL =		https://github.com/giampaolo/psutil
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/a0/d0/c9ae661a302931735237791f04cb7086ac244377f78692ba3b3eae3a9619/psutil-5.9.7.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:3f02134e82cfb5d089fddf20bb2e03fd5cd52395321d1c8458a9e58500ff417c
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# We need to run tests in proto area to get access to compiled modules
COMPONENT_TEST_DIR = $(PROTO_DIR)/$(PYTHON_LIB)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
