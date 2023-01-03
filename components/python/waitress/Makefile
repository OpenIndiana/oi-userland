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
#   $WS_TOOLS/python-integrate-project waitress
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		waitress
HUMAN_VERSION =			2.1.2
COMPONENT_SUMMARY =		waitress - Waitress WSGI server
COMPONENT_PROJECT_URL =		https://github.com/Pylons/waitress
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/72/83/c3de9799e2305898b02ea67bcd125ad06f271e2a82cc86fe66b7bf4e6f63/waitress-2.1.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:780a4082c5fbc0fde6a2fcfe5e26e6efc1e8f425730863c04085769781f51eba
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
