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
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zconfig
HUMAN_VERSION =			4.3
COMPONENT_SUMMARY =		Structured Configuration Library
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/ZConfig/
COMPONENT_ARCHIVE_HASH =	\
	sha256:472233e515fa29be6c873e78b8a2b450c2cd25d0133cb45960837f33f1ab4fe3
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# To solve simliar problem like
# https://github.com/zopefoundation/persistent/issues/183
COMPONENT_POST_UNPACK_ACTION += \
	$(RM) $(SOURCE_DIR)/src/ZConfig/tests/test_readme.py ;

# Force no colors and more verbose output via tox posargs
TOX_POSARGS += -vv

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/docutils
TEST_REQUIRED_PACKAGES.python += library/python/manuel
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/zope-exceptions
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
