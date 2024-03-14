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
#   $WS_TOOLS/python-integrate-project extras
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		extras
COMPONENT_VERSION =		1.0.0
COMPONENT_SUMMARY =		extras - Useful extra bits for Python - things that shold be in the standard library
COMPONENT_PROJECT_URL =		https://github.com/testing-cabal/extras
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/be/18/0b7283f0ebf6ad4bb6b9937538495eadf05ef097b102946b9445c4242636/extras-1.0.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:132e36de10b9c91d5d4cc620160a476e0468a88f16c9431817a6729611a81b4e
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# extras --> testtools ==> extras
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# extras needs testtools to run tests, but currently there is no way to detect
# that automatically
TEST_REQUIRED_PACKAGES.python += library/python/testtools

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
