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
#   $WS_TOOLS/python-integrate-project -d python/elastic-transport elastic_transport
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		elastic_transport
HUMAN_VERSION =			8.15.0
COMPONENT_SUMMARY =		Transport classes and utilities shared among Python Elastic client libraries
COMPONENT_PROJECT_URL =		https://github.com/elastic/elastic-transport-python
COMPONENT_ARCHIVE_HASH =	\
	sha256:85d62558f9baafb0868c801233a59b235e61d7b4804c28c2fadaa866b6766233
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += develop

# We do not have respx
PYTEST_ADDOPTS += --ignore tests/node/test_http_httpx.py
# We do not have opentelemetry
PYTEST_ADDOPTS += --ignore tests/test_otel.py
# We do not have orjson
PYTEST_ADDOPTS += --ignore tests/test_serializer.py

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/certifi
PYTHON_REQUIRED_PACKAGES += library/python/urllib3
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/aiohttp
TEST_REQUIRED_PACKAGES.python += library/python/httpx
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-asyncio
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-httpserver
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/requests
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/sphinx-autodoc-typehints
TEST_REQUIRED_PACKAGES.python += library/python/trustme
