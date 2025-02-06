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

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zconfig
HUMAN_VERSION =			4.2
COMPONENT_SUMMARY =		Structured Configuration Library
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/ZConfig/
COMPONENT_ARCHIVE_HASH =	\
	sha256:a0e4b5277c4cee8060ce335a578ac458f82c240ae96b16659200dbc4d98bfcce
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
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/docutils
TEST_REQUIRED_PACKAGES.python += library/python/manuel
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/zope-exceptions
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
