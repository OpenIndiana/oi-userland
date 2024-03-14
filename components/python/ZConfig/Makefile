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
#   $WS_TOOLS/python-integrate-project ZConfig
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		ZConfig
HUMAN_VERSION =			4.0
COMPONENT_SUMMARY =		ZConfig - Structured Configuration Library
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/ZConfig/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/05/1b/24f8eba7b5a51beed8eb256f08610afeddde3190475fa4f342902e4f7a0e/ZConfig-4.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f8d642fba6ba98d08631be2c1f71ad1957c051fef4aa3d3fb9f1e08dc61d0156
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
