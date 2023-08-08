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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pydantic
HUMAN_VERSION =			1.10.12
COMPONENT_SUMMARY =		pydantic - Data validation using Python type hints
COMPONENT_PROJECT_URL =		https://github.com/pydantic/pydantic
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/3b/9b/a7631bf35e55326fd74654fe6bd896478f47d65e97ca69e60ddb1b3823ee/pydantic-1.10.12.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:0fe8a415cea8f340e7a9af9c54fc71a649b43e8ca3cc732986116b3cb135d303
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy
# https://github.com/pydantic/pydantic/issues/5561
PYTEST_ADDOPTS += -p no:randomly

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
