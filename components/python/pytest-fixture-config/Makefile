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
#   $WS_TOOLS/python-integrate-project pytest-fixture-config
#

BUILD_STYLE = setup.py
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest-fixture-config
HUMAN_VERSION =			1.7.0
COMPONENT_SUMMARY =		pytest-fixture-config - Fixture configuration utils for py.test
COMPONENT_PROJECT_URL =		https://github.com/manahl/pytest-plugins
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/07/19/37fe282f262b65247e310ec59223329e1ad53a71683f81a139e7d9ca7916/pytest-fixture-config-1.7.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:41a17417721f6862ce6b40e3280fddd8e1659b2c306ec46b237d7021fec5218e
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Testing fails with the checkdocs plugin installed
PYTEST_ADDOPTS += -p no:checkdocs

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += runtime/python
