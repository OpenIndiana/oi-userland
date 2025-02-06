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
HUMAN_VERSION =			4.2.2
COMPONENT_SUMMARY =		Fixtures, reusable state for writing clean tests and more.
COMPONENT_PROJECT_URL =		https://github.com/testing-cabal/fixtures
COMPONENT_ARCHIVE_HASH =	\
	sha256:af9368737fad6fd501638ca99c78000c3f3fb03fa40a60f9e9d39aa64f342bc1
COMPONENT_LICENSE =		Apache-2.0 OR BSD-3-Clause

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# fixtures --> testtools ==> fixtures
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pbr
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/docutils
TEST_REQUIRED_PACKAGES.python += library/python/testtools
