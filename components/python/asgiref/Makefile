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
#   $WS_TOOLS/python-integrate-project asgiref
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		asgiref
HUMAN_VERSION =			3.8.0
COMPONENT_SUMMARY =		asgiref - ASGI specs, helper code, and adapters
COMPONENT_PROJECT_URL =		https://github.com/django/asgiref/
COMPONENT_ARCHIVE_URL =		\
	https://github.com/django/asgiref/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:7c9a06aa745ddb00b70b9b7f24f8481afcffecf778d889128c17560fda2ff290
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# https://github.com/django/asgiref/issues/450
COMPONENT_TEST_TRANSFORMS += "-e '/^task: /d'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/mypy
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-asyncio
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
