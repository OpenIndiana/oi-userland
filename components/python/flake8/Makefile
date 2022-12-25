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
#   $WS_TOOLS/python-integrate-project flake8
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		flake8
HUMAN_VERSION =			5.0.4
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		flake8 - the modular source code checker: pep8 pyflakes and co
COMPONENT_PROJECT_URL =		https://github.com/pycqa/flake8
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ad/00/9808c62b2d529cefc69ce4e4a1ea42c0f855effa55817b7327ec5b75e60a/flake8-5.0.4.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:6fbe320aad8d6b95cec8b8e47bc933004678dc63095be98528b7bdd2a9f510db
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# The test_local_plugin_can_add_option depends on list of installed flake8
# plugins.  To get consistent test results we need to make sure flake8-2020 is
# always installed.
TEST_REQUIRED_PACKAGES.python += library/python/flake8-2020

# Warning: With flake8-noqa installed some tests fail so to see all tests
# passed the flake8-noqa should not be installed.

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/mccabe
PYTHON_REQUIRED_PACKAGES += library/python/pycodestyle
PYTHON_REQUIRED_PACKAGES += library/python/pyflakes
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/pytest
