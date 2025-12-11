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
#   $WS_TOOLS/python-integrate-project -d python/BTrees-39 btrees
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		btrees
HUMAN_VERSION =			6.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Scalable persistent object containers
COMPONENT_ARCHIVE_HASH =	\
	sha256:e18746f8641869a20f45328c9b5f97dc6c71a1195960356aef63b75f5c8d445f
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

# BTrees >= 6.2 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
TOX_POSARGS += -vv

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/persistent
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += library/python/zope-interface
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/persistent
TEST_REQUIRED_PACKAGES.python += library/python/repoze-sphinx-autointerface
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/sphinx-rtd-theme
TEST_REQUIRED_PACKAGES.python += library/python/transaction
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
