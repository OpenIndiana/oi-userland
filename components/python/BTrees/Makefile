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
#   $WS_TOOLS/python-integrate-project BTrees
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		BTrees
HUMAN_VERSION =			5.0
COMPONENT_SUMMARY =		BTrees - Scalable persistent object containers
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/BTrees
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/a6/da/c222526a5c1effff5557ebb44dfd24a01f58e52fe244e0af21a248464f18/BTrees-5.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:fddf8a4dcc0253e39027bab380a2e20d47ae370a32485416f2a66ad9ae1a43fa
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/persistent
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += library/python/zope-interface
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/persistent
TEST_REQUIRED_PACKAGES.python += library/python/repoze-sphinx-autointerface
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/sphinx-rtd-theme
TEST_REQUIRED_PACKAGES.python += library/python/transaction
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
