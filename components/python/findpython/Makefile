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
#   $WS_TOOLS/python-integrate-project findpython
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		findpython
HUMAN_VERSION =			0.9.0
COMPONENT_SUMMARY =		A utility to find python versions on your system
COMPONENT_PROJECT_URL =		https://github.com/frostming/findpython
COMPONENT_ARCHIVE_HASH =	\
	sha256:497c6b5eb13734be2542dfb6a93267946339601cbc2f1138c8cd4d40311fefe5
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# Python 3.9 is not supported by findpython >= 0.9.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/packaging
REQUIRED_PACKAGES.python += library/python/pdm-backend
REQUIRED_PACKAGES.python += library/python/platformdirs
REQUIRED_PACKAGES.python += runtime/python
