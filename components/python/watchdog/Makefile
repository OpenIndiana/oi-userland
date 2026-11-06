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
#   $WS_TOOLS/python-integrate-project watchdog
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		watchdog
HUMAN_VERSION =			7.1.0
COMPONENT_SUMMARY =		Filesystem events monitoring
COMPONENT_PROJECT_URL =		https://github.com/gorakhargosh/watchdog
COMPONENT_ARCHIVE_HASH =	\
	sha256:d3861e255416f49a1384474cb2efa097de165fb330d4c5432ce6708b509ed922
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# Python 3.9 is not supported by watchdog >= 7.0.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# https://github.com/gorakhargosh/watchdog/issues/10
PYTEST_ADDOPTS += --ignore=tests/test_emitter.py

# https://github.com/gorakhargosh/watchdog/issues/973
PYTEST_ADDOPTS += --deselect tests/test_0_watchmedo.py::test_auto_restart_on_file_change_debounce

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/flaky
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/pyyaml
