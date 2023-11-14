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
#   $WS_TOOLS/python-integrate-project dulwich
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		dulwich
HUMAN_VERSION =			0.21.6
COMPONENT_SUMMARY =		dulwich - Python Git Library
COMPONENT_PROJECT_URL =		https://www.dulwich.io/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/57/e0/1b5f95c2651284a5d4fdfb2cc5ecad57fb694084cce59d9d4acb7ac30ecf/dulwich-0.21.6.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:30fbe87e8b51f3813c131e2841c86d007434d160bd16db586b40d47f31dd05b0
COMPONENT_LICENSE =		Apache-2.0 OR GPL-2.0-only
COMPONENT_LICENSE_FILE =	COPYING

# see tox.ini
TEST_STYLE = unittest

include $(WS_MAKE_RULES)/common.mk

# see tox.ini
COMPONENT_TEST_TARGETS = dulwich.tests.test_suite

# Normalize pointers
COMPONENT_TEST_TRANSFORMS += "-e 's/0x[0-9a-f]\{12\}/\$$(POINTER)/g'"
# Normalize timetstamps that change with every run
COMPONENT_TEST_TRANSFORMS += "-e 's|\[../.../.... ..:..:..\]|[XX/XXX/XXXX XX:XX:XX]|'"
# Remove line that could be out of order and contains random port number
COMPONENT_TEST_TRANSFORMS += "-e '/^Push to /d'"
# Normalize port
COMPONENT_TEST_TRANSFORMS += "-e 's/\(laddr=('\''127.0.0.1'\'', \)[0-9]\{1,\})/\1\$$(PORT))/'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/urllib3
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
