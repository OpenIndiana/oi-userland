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
#   $WS_TOOLS/python-integrate-project -d python/pyproject-metadata pyproject_metadata
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyproject_metadata
HUMAN_VERSION =			0.10.0
COMPONENT_SUMMARY =		PEP 621 metadata parsing
COMPONENT_PROJECT_URL =		https://github.com/pypa/pyproject-metadata
COMPONENT_ARCHIVE_HASH =	\
	sha256:7f5bd0ef398b60169556cb17ea261d715caf7f8561238151f51b2305084ba8d4
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Test results order varies between runs
PYTEST_SORT_TESTS = yes

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += library/python/packaging
REQUIRED_PACKAGES.python += runtime/python
