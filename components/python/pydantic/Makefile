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
#   $WS_TOOLS/python-integrate-project pydantic
#

BUILD_STYLE = setup.py
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pydantic
HUMAN_VERSION =			1.10.8
COMPONENT_SUMMARY =		pydantic - Data validation and settings management using python type hints
COMPONENT_PROJECT_URL =		https://github.com/pydantic/pydantic
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/23/65/2aa13873e9e0084ecaec00fbe6c6096b65e1ab99ba66bdbf7e4e7c4cc915/pydantic-1.10.8.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:1410275520dfa70effadf4c21811d755e7ef9bb1f1d077a21958153a92c8d9ca
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# https://github.com/pydantic/pydantic/issues/5561
PYTEST_ADDOPTS += -p no:randomly

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
