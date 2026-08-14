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
#   $WS_TOOLS/python-integrate-project -d python/pytest-rerunfailures pytest_rerunfailures
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest_rerunfailures
HUMAN_VERSION =			16.5
COMPONENT_SUMMARY =		pytest plugin to re-run tests to eliminate flaky failures
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-rerunfailures
COMPONENT_ARCHIVE_HASH =	\
	sha256:1481b45e6eb73228d19979c4481a8532007fadc6881d1198622cad1901c4afb2
COMPONENT_LICENSE =		MPL-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# Python 3.9 is not supported by pytest-rerunfailures >= 16.1
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/packaging
REQUIRED_PACKAGES.python += library/python/pytest
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
