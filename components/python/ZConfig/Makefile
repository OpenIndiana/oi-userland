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
#   $WS_TOOLS/python-integrate-project -d python/ZConfig zconfig
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zconfig
HUMAN_VERSION =			4.1
COMPONENT_SUMMARY =		zconfig - Structured Configuration Library
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/ZConfig/
COMPONENT_ARCHIVE_HASH =	\
	sha256:b6a79dda157f3698c8768d2cedc263216e8af240d3cf9d09a02a64291114eb20
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# To solve simliar problem like
# https://github.com/zopefoundation/persistent/issues/183
COMPONENT_POST_UNPACK_ACTION += \
	$(RM) $(SOURCE_DIR)/src/ZConfig/tests/test_readme.py ;

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/docutils
TEST_REQUIRED_PACKAGES.python += library/python/manuel
TEST_REQUIRED_PACKAGES.python += library/python/zope-exceptions
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
