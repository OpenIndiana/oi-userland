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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zodb
HUMAN_VERSION =			6.0.1
COMPONENT_SUMMARY =		ZODB, a Python object-oriented database
COMPONENT_PROJECT_URL =		http://zodb-docs.readthedocs.io
COMPONENT_ARCHIVE_HASH =	\
	sha256:89f70fae1852123e243547909c311441d63405dec26f6ec42f365a2191db9509
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
PYTHON_REQUIRED_PACKAGES += library/python/persistent
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/transaction
PYTHON_REQUIRED_PACKAGES += library/python/zc-lockfile
PYTHON_REQUIRED_PACKAGES += library/python/zconfig
PYTHON_REQUIRED_PACKAGES += library/python/zodbpickle
PYTHON_REQUIRED_PACKAGES += library/python/zope-interface
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/manuel
TEST_REQUIRED_PACKAGES.python += library/python/zope-testing
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
