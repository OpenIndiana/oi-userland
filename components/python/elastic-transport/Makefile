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
#   $WS_TOOLS/python-integrate-project elastic-transport
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		elastic-transport
HUMAN_VERSION =			8.12.0
COMPONENT_SUMMARY =		elastic-transport - Transport classes and utilities shared among Python Elastic client libraries
COMPONENT_PROJECT_URL =		https://github.com/elastic/elastic-transport-python
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/f1/5e/9d697ca2511c2ecb3a239be91d5186a14fdbc97e15369c4ca6524c2929e8/elastic-transport-8.12.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:48839b942fcce199eece1558ecea6272e116c58da87ca8d495ef12eb61effaf7
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += develop

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/certifi
PYTHON_REQUIRED_PACKAGES += library/python/urllib3
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/aiohttp
TEST_REQUIRED_PACKAGES.python += library/python/mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-asyncio
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-httpserver
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/requests
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/sphinx-autodoc-typehints
TEST_REQUIRED_PACKAGES.python += library/python/trustme
