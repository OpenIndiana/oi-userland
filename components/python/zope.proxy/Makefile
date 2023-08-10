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
#   $WS_TOOLS/python-integrate-project zope.proxy
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope.proxy
HUMAN_VERSION =			5.0.0
COMPONENT_SUMMARY =		zope.proxy - Generic Transparent Proxies
COMPONENT_PROJECT_URL =		http://github.com/zopefoundation/zope.proxy
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ec/93/e2fbb3c34cdd29ba09909c25c0153522a59939f84f15cc0c88865780f1d7/zope.proxy-5.0.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:6fa44c97a412b4dc51e2f5fd4dc73c5bd499d35280f88cd2bcd26f8ae1e4577b
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# zope.proxy --> zope.security ==> zope.proxy
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/zope-interface
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/repoze-sphinx-autointerface
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/zope-security
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
