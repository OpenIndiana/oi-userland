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
#   $WS_TOOLS/python-integrate-project pytest-lazy-fixtures
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest-lazy-fixtures
HUMAN_VERSION =			1.0.5
COMPONENT_SUMMARY =		pytest-lazy-fixtures - Allows you to use fixtures in @pytest.mark.parametrize.
COMPONENT_PROJECT_URL =		https://github.com/dev-petrov/pytest-lazy-fixtures
COMPONENT_ARCHIVE_URL =		\
	https://github.com/dev-petrov/pytest-lazy-fixtures/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:c99e8969a67d2e2a2cefc7f36151dcb5b52e0c4080e538775ead9ff349eebc2c
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# https://github.com/dev-petrov/pytest-lazy-fixtures/issues/10
COMPONENT_TEST_ENV += PYTEST_DISABLE_PLUGIN_AUTOLOAD=1

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/poetry-core
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += runtime/python
