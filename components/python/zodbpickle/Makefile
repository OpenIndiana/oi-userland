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
#   $WS_TOOLS/python-integrate-project zodbpickle
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zodbpickle
HUMAN_VERSION =			3.0.1
COMPONENT_SUMMARY =		zodbpickle - Fork of Python 3 pickle module.
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/zodbpickle
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/2f/ff/68ad84892488418896004278c0e88bb87b2a8654c9e387d03ac7016bcd87/zodbpickle-3.0.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:0f0975bdd4a7615320e74af2b0b8be4763c73cf8bf7c4212ab72044289e77498
COMPONENT_LICENSE =		PSF-2.0 OR ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
