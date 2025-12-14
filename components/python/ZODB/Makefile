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
#   $WS_TOOLS/python-integrate-project -d python/ZODB zodb
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zodb
HUMAN_VERSION =			6.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		ZODB, a Python object-oriented database
COMPONENT_PROJECT_URL =		http://zodb-docs.readthedocs.io
COMPONENT_ARCHIVE_HASH =	\
	sha256:854a269f78977cdfda06aff08e93a8aa512c214202caae301222db2ef98ba365
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# To solve simliar problem like
# https://github.com/zopefoundation/persistent/issues/183
COMPONENT_POST_UNPACK_ACTION += \
	$(RM) $(SOURCE_DIR)/src/ZODB/tests/testdocumentation.py ;

# Force no colors and more verbose output via tox posargs
TOX_POSARGS += -vv

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/btrees
REQUIRED_PACKAGES.python += library/python/persistent
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/transaction
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += library/python/zc-lockfile
REQUIRED_PACKAGES.python += library/python/zconfig
REQUIRED_PACKAGES.python += library/python/zodbpickle
REQUIRED_PACKAGES.python += library/python/zope-interface
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/manuel
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/zope-testing
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
