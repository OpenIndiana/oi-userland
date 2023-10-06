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
#   $WS_TOOLS/python-integrate-project zope.interface
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope.interface
HUMAN_VERSION =			6.1
COMPONENT_SUMMARY =		zope.interface - Interfaces for Python
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/zope.interface
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/87/03/6b85c1df2dca1b9acca38b423d1e226d8ffdf30ebd78bcb398c511de8b54/zope.interface-6.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:2fdc7ccbd6eb6b7df5353012fbed6c3c5d04ceaca0038f75e601060e95345309
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# zope.interface --> repoze.sphinx.autointerface ==> zope.interface
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# verbose test output
COMPONENT_TEST_TARGETS += -- --verbose
# https://github.com/zopefoundation/zope.interface/issues/196
COMPONENT_TEST_TARGETS += -s $(PROTO_DIR)/$(PYTHON_LIB)/zope/interface -t $(PROTO_DIR)/$(PYTHON_LIB)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/repoze-sphinx-autointerface
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/sphinx-rtd-theme
TEST_REQUIRED_PACKAGES.python += library/python/zope-event
TEST_REQUIRED_PACKAGES.python += library/python/zope-testing
