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
#   $WS_TOOLS/python-integrate-project wheel
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		wheel
COMPONENT_VERSION =		0.38.2
COMPONENT_SUMMARY =		wheel - A built-package format for Python
COMPONENT_PROJECT_URL =		https://github.com/pypa/wheel
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/a4/5b/0718aa11e3360f97feb81ddcb19cbb9306df0a17bef7c360f8939d2629b8/wheel-0.38.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:3d492ef22379a156ec923d2a77051cedfd4df4b667864e9e41ba83f0b70b7149
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - packaging
PYTHON_BOOTSTRAP = yes

# Disable tests because required packages are not available during bootstrap
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib_metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
