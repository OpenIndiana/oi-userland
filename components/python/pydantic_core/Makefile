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
#   $WS_TOOLS/python-integrate-project pydantic_core
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pydantic_core
HUMAN_VERSION =			2.18.0
COMPONENT_SUMMARY =		pydantic_core - Core functionality for Pydantic validation and serialization
COMPONENT_PROJECT_URL =		https://github.com/pydantic/pydantic-core
COMPONENT_ARCHIVE_HASH =	\
	sha256:a6d075404af8b8feb42f86196e08053bfae282af2701321f36a1553e966ce1f0
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# pydantic_core --> dirty_equals --> pydantic ==> pydantic_core
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# https://www.illumos.org/issues/15767
LD_Z_IGNORE=

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += tests/requirements.txt
TEST_REQUIRED_PACKAGES.python += library/python/pytest-benchmark

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/maturin
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/dirty-equals
TEST_REQUIRED_PACKAGES.python += library/python/exceptiongroup
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/pytz
