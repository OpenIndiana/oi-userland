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
#   $WS_TOOLS/python-integrate-project httpcore
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		httpcore
HUMAN_VERSION =			1.0.9
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		A minimal low-level HTTP client.
COMPONENT_PROJECT_URL =		https://www.encode.io/httpcore/
COMPONENT_ARCHIVE_HASH =	\
	sha256:6e34463af53fd2ab5d807f399a9b45ea31c3dfa2276f15a2c3f00afff6e176e8
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.md

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += http2
TEST_REQUIREMENTS_EXTRAS += socks
TEST_REQUIREMENTS_EXTRAS += asyncio

# Test dependencies we are unable to detect automatically
TEST_REQUIRED_PACKAGES.python += library/python/hpack
TEST_REQUIRED_PACKAGES.python += library/python/hyperframe

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/certifi
REQUIRED_PACKAGES.python += library/python/h11
REQUIRED_PACKAGES.python += library/python/hatch-fancy-pypi-readme
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/anyio
TEST_REQUIRED_PACKAGES.python += library/python/h2
TEST_REQUIRED_PACKAGES.python += library/python/socksio
