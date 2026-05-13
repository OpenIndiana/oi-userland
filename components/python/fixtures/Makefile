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
#   $WS_TOOLS/python-integrate-project fixtures
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		fixtures
HUMAN_VERSION =			4.3.2
COMPONENT_SUMMARY =		Fixtures, reusable state for writing clean tests and more.
COMPONENT_PROJECT_URL =		https://github.com/testing-cabal/fixtures
COMPONENT_ARCHIVE_HASH =	\
	sha256:b7db64014732513f23d12b0c49ae527ba0c0c1f2667ec97d9136d67157ebce5d
COMPONENT_LICENSE =		Apache-2.0 OR BSD-3-Clause

# Python 3.9 is not supported by fixtures >= 4.2.7
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Testing needs to find the tests module in the build directory
COMPONENT_TEST_ENV += PYTHONPATH=$(PROTOPYTHONVENDORDIR):$(COMPONENT_TEST_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/docutils
TEST_REQUIRED_PACKAGES.python += library/python/testtools
