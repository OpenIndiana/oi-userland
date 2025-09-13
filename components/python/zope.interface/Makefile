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
#   $WS_TOOLS/python-integrate-project -d python/zope.interface zope_interface
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope_interface
HUMAN_VERSION =			8.0
COMPONENT_SUMMARY =		Interfaces for Python
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/zope.interface
COMPONENT_ARCHIVE_HASH =	\
	sha256:b14d5aac547e635af749ce20bf49a3f5f93b8a854d2a6b1e95d4d5e5dc618f7d
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# force verbose test output via tox posargs
TOX_POSARGS += --verbose
# https://github.com/zopefoundation/zope.interface/issues/196
TOX_POSARGS += -s $(PROTO_DIR)/$(PYTHON_LIB)/zope/interface -t $(PROTO_DIR)/$(PYTHON_LIB)/zope

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/repoze-sphinx-autointerface
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/tomli
TEST_REQUIRED_PACKAGES.python += library/python/zope-event
TEST_REQUIRED_PACKAGES.python += library/python/zope-testing
