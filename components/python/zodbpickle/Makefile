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

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zodbpickle
HUMAN_VERSION =			4.5
COMPONENT_SUMMARY =		Fork of Python 3 pickle module
COMPONENT_ARCHIVE_HASH =	\
	sha256:67d4295ddb68b2410fe417094ffe1a8b0ed41834ee308020f58ee1b633e1f751
COMPONENT_LICENSE =		PSF-2.0 OR ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

# Python 3.9 is not supported by zodbpickle >= 4.3
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
TOX_POSARGS += -vv

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
