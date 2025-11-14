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
#   $WS_TOOLS/python-integrate-project -d python/ephemeral_port_reserve ephemeral-port-reserve
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		ephemeral-port-reserve
HUMAN_VERSION =			1.1.4
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Bind to an ephemeral port, force it into the TIME_WAIT state, and unbind it.
COMPONENT_PROJECT_URL =		https://github.com/Yelp/ephemeral-port-reserve/
COMPONENT_ARCHIVE_URL =		\
	https://github.com/Yelp/ephemeral-port-reserve/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:522a3b80e885c62b9561c4150cefda7a67cad954d22d474c6f9362348828e079
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# https://www.illumos.org/issues/17745
PYTEST_ADDOPTS += --deselect tests/ephemeral_port_test.py::test_localhost
PYTEST_ADDOPTS += --deselect tests/ephemeral_port_test.py::test_fqdn

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest
