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
#   $WS_TOOLS/python-integrate-project -d python/Chameleon chameleon
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		chameleon
HUMAN_VERSION =			4.6.1
COMPONENT_SUMMARY =		Fast HTML/XML Template Compiler.
COMPONENT_PROJECT_URL =		https://chameleon.readthedocs.io
COMPONENT_ARCHIVE_HASH =	\
	sha256:c1775d54907966c8e397a1292b1a2755d254b7f070d0719ac9e579d9ab81e5b5
COMPONENT_LICENSE =		BSD-3-Clause OR PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

# Python 3.9 is not supported by Chameleon >= 4.6.1
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Test results order varies between runs
PYTEST_SORT_TESTS = yes

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/build
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/wheel
