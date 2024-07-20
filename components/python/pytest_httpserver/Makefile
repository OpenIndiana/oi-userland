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
#   $WS_TOOLS/python-integrate-project pytest_httpserver
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest_httpserver
HUMAN_VERSION =			1.0.11
COMPONENT_SUMMARY =		pytest-httpserver is a httpserver for pytest
COMPONENT_PROJECT_URL =		https://github.com/csernazs/pytest-httpserver
COMPONENT_ARCHIVE_HASH =	\
	sha256:834531f278e99a22cf3920bc30fe06784518b742a189628b3b34953604ad83f6
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# https://github.com/csernazs/pytest-httpserver/issues/345
PYTEST_ADDOPTS += --deselect tests/test_log_querying.py::test_verify_assert_msg
PYTEST_ADDOPTS += --deselect tests/test_log_querying.py::test_verify_assert_msg_no_similar_requests

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/poetry-core
PYTHON_REQUIRED_PACKAGES += library/python/werkzeug
PYTHON_REQUIRED_PACKAGES += runtime/python
