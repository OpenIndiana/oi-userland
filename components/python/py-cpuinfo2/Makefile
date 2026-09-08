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
#   $WS_TOOLS/python-integrate-project -d python/py-cpuinfo2 py_cpuinfo2
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		py_cpuinfo2
HUMAN_VERSION =			10.1.1
COMPONENT_SUMMARY =		Get CPU info with pure Python
COMPONENT_PROJECT_URL =		https://github.com/akx/py-cpuinfo2
COMPONENT_ARCHIVE_HASH =	\
	sha256:7861133863663f16e06eca63b12904ef100b5760415e92372dac0162799a4771
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# We do not need py-cpuinfo2 for Python 3.9
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
