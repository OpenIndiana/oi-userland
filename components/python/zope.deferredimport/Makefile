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
#   $WS_TOOLS/python-integrate-project -d python/zope.deferredimport zope_deferredimport
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope_deferredimport
HUMAN_VERSION =			5.1
COMPONENT_SUMMARY =		zope.deferredimport allows you to perform imports names that will only be resolved when used in the code.
COMPONENT_PROJECT_URL =		http://github.com/zopefoundation/zope.deferredimport
COMPONENT_ARCHIVE_HASH =	\
	sha256:9a4781b4382cbdb53f661a2b45a0acca8c22b5af835a49f99b548ac9c16d06ef
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
TOX_POSARGS += -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += library/python/zope-proxy
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/repoze-sphinx-autointerface
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
