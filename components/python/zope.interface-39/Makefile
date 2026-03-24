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
#   $WS_TOOLS/python-integrate-project -d python/zope.interface-39 zope_interface
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope_interface
HUMAN_VERSION =			8.0.1
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Interfaces for Python
COMPONENT_ARCHIVE_HASH =	\
	sha256:eba5610d042c3704a48222f7f7c6ab5b243ed26f917e2bc69379456b115e02d1
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

COMPONENT_VERSION =		8.1.1

# zope.interface >= 8.1 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

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
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/zope-event
TEST_REQUIRED_PACKAGES.python += library/python/zope-testing
