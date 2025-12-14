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
#   $WS_TOOLS/python-integrate-project httpx
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		httpx
HUMAN_VERSION =			0.28.1
COMPONENT_SUMMARY =		The next generation HTTP client.
COMPONENT_PROJECT_URL =		https://github.com/encode/httpx
COMPONENT_ARCHIVE_URL =		\
	https://github.com/encode/httpx/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:61fe412dd34b6d95197feb9dbfb6a6e2c749197b67287b2f75925ec257bb41ae
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.md

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Random temporary directory name
# see also https://github.com/encode/httpx/discussions/3016
COMPONENT_TEST_TRANSFORMS += "-e '/\/tmp\/.*garbage/d'"

# https://github.com/encode/httpx/issues/3708
# https://github.com/encode/httpx/pull/3720#issuecomment-3734335590
TEST_CONFLICTING_PACKAGES.python += library/python/websockets

# https://github.com/encode/httpx/discussions/3743
PYTEST_ADDOPTS += --deselect tests/test_main.py

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += requirements.txt

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/anyio
REQUIRED_PACKAGES.python += library/python/certifi
REQUIRED_PACKAGES.python += library/python/hatch-fancy-pypi-readme
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += library/python/httpcore
REQUIRED_PACKAGES.python += library/python/idna
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/chardet
TEST_REQUIRED_PACKAGES.python += library/python/cryptography
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/socksio
TEST_REQUIRED_PACKAGES.python += library/python/trustme
TEST_REQUIRED_PACKAGES.python += library/python/uvicorn
TEST_REQUIRED_PACKAGES.python += library/python/zstandard
