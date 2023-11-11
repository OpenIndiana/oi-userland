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
HUMAN_VERSION =			1.0.2
COMPONENT_SUMMARY =		httpcore - A minimal low-level HTTP client.
COMPONENT_PROJECT_URL =		https://www.encode.io/httpcore/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/18/56/78a38490b834fa0942cbe6d39bd8a7fd76316e8940319305a98d2b320366/httpcore-1.0.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:9fc092e4799b26174648e54b74ed5f683132a464e95643b226e00c2ed2fa6535
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.md

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += http2
TEST_REQUIREMENTS_EXTRAS += asyncio

# Test dependencies we are unable to detect automatically
TEST_REQUIRED_PACKAGES.python += library/python/hpack
TEST_REQUIRED_PACKAGES.python += library/python/hyperframe

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/certifi
PYTHON_REQUIRED_PACKAGES += library/python/h11
PYTHON_REQUIRED_PACKAGES += library/python/hatch-fancy-pypi-readme
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/anyio
TEST_REQUIRED_PACKAGES.python += library/python/h2
