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
#   $WS_TOOLS/python-integrate-project pygments
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pygments
HUMAN_VERSION =			2.20.0
COMPONENT_SUMMARY =		Pygments is a syntax highlighting package written in Python.
COMPONENT_PROJECT_URL =		https://pygments.org
COMPONENT_ARCHIVE_HASH =	\
	sha256:6757cd03768053ff99f3039c1a36d6c0aa0b263438fcab17520b30a303a82b5f
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - pytest (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-randomly
TEST_REQUIRED_PACKAGES.python += library/python/wcag-contrast-ratio
