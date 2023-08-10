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
#   $WS_TOOLS/python-integrate-project transaction
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		transaction
HUMAN_VERSION =			3.1.0
COMPONENT_SUMMARY =		transaction - Transaction management for Python
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/transaction
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/e0/12/76ce5ff26e7a24ff21d5d185ef6ca203f5820177f8e6a5dd354365fc4dbd/transaction-3.1.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:65d0b1ea92dbe7c4e3b237fb6bd8b41dea23d7459e7bdd8c3880bffdaf912fa4
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/zope-interface
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/mock
TEST_REQUIRED_PACKAGES.python += library/python/repoze-sphinx-autointerface
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
