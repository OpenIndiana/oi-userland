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
#   $WS_TOOLS/python-integrate-project ZODB
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		ZODB
HUMAN_VERSION =			5.8.1
COMPONENT_SUMMARY =		ZODB - ZODB, a Python object-oriented database
COMPONENT_PROJECT_URL =		http://zodb-docs.readthedocs.io
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/68/8f/ba84246f531ffe594f78e417ab9069673e2ffd12f210939f42d2c1b86aa9/ZODB-5.8.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:c6c73abd3660d606ffc1f21f97def14b52b46f4a702ec9e6ee449a6e2be264df
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# To solve simliar problem like
# https://github.com/zopefoundation/persistent/issues/183
COMPONENT_POST_UNPACK_ACTION += \
	$(RM) $(SOURCE_DIR)/src/ZODB/tests/testdocumentation.py ;

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/btrees
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/persistent
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/six
PYTHON_REQUIRED_PACKAGES += library/python/transaction
PYTHON_REQUIRED_PACKAGES += library/python/zc-lockfile
PYTHON_REQUIRED_PACKAGES += library/python/zconfig
PYTHON_REQUIRED_PACKAGES += library/python/zodbpickle
PYTHON_REQUIRED_PACKAGES += library/python/zope-interface
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/manuel
TEST_REQUIRED_PACKAGES.python += library/python/zope-testing
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
