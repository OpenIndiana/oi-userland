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
#   $WS_TOOLS/python-integrate-project cffi
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cffi
HUMAN_VERSION =			1.16.0
COMPONENT_SUMMARY =		cffi - Foreign Function Interface for Python calling C code.
COMPONENT_PROJECT_URL =		http://cffi.readthedocs.org
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/68/ce/95b0bae7968c65473e1298efb042e10cafc7bafc14d9e4f154008241c91d/cffi-1.16.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:bcb3ef43e58665bbda2fb198698fcae6776483e0c4a631aa5647806c25e02cc0
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Set full path to gcc for testing
COMPONENT_PREP_ACTION = $(GSED) -i -e 's|cc|'"$(CC.$(COMPILER).$(BUILD_BITS))"'|' $(@D)/testing/cffi0/test_ownlib.py

# Testing needs to find gcc
COMPONENT_TEST_ENV += PATH="$(GCC_BINDIR):$(PATH)"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pycparser
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += system/library
