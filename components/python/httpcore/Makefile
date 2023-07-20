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

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		httpcore
HUMAN_VERSION =			0.17.3
COMPONENT_SUMMARY =		httpcore - A minimal low-level HTTP client.
COMPONENT_PROJECT_URL =		https://github.com/encode/httpcore
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/63/ad/c98ecdbfe04417e71e143bf2f2fb29128e4787d78d1cedba21bd250c7e7a/httpcore-0.17.3.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:a6f30213335e34c1ade7be6ec7c47f19f50c56db36abef1a9dfa3815b1cb3888
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.md

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy

# Test dependencies we are unable to detect automatically
TEST_REQUIRED_PACKAGES.python += library/python/hpack
TEST_REQUIRED_PACKAGES.python += library/python/hyperframe

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/anyio
PYTHON_REQUIRED_PACKAGES += library/python/certifi
PYTHON_REQUIRED_PACKAGES += library/python/h11
PYTHON_REQUIRED_PACKAGES += library/python/sniffio
PYTHON_REQUIRED_PACKAGES += runtime/python
