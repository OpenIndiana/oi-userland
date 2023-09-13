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
#   $WS_TOOLS/python-integrate-project pytest-perf
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest-perf
HUMAN_VERSION =			0.13.1
COMPONENT_SUMMARY =		pytest-perf - Run performance tests against the mainline code.
COMPONENT_PROJECT_URL =		https://github.com/jaraco/pytest-perf
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/d2/74/8c112d99f595dc1718225ba50709ee3ed14a6f480bba7e5428a78ffaa94a/pytest-perf-0.13.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:0ec3bfeb0c8a6dcb8b1d3ea4ed1abb0b26685cfaff584e733395bd09608ab5a2
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Tests require working git repo:
# https://github.com/jaraco/pytest-perf/issues/6
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-context
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-functools
PYTHON_REQUIRED_PACKAGES += library/python/more-itertools
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/pip-run
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/tempora
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
