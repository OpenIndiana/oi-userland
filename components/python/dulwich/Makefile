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
HUMAN_VERSION =			0.22.3
COMPONENT_SUMMARY =		Python Git Library
COMPONENT_PROJECT_URL =		https://www.dulwich.io/
COMPONENT_ARCHIVE_HASH =	\
	sha256:7968c7b8a877b614c46b5ee7c1b28411772123004d7cf6357e763ad2cbeb8254
COMPONENT_LICENSE =		Apache-2.0 OR GPL-2.0-only
COMPONENT_LICENSE_FILE =	COPYING

# see tox.ini
TEST_STYLE = unittest

include $(WS_MAKE_RULES)/common.mk

# see tox.ini
COMPONENT_TEST_TARGETS = tests.test_suite

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
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-rust
PYTHON_REQUIRED_PACKAGES += library/python/urllib3
PYTHON_REQUIRED_PACKAGES += runtime/python
