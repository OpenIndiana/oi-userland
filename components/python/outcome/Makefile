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
#   $WS_TOOLS/python-integrate-project outcome
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		outcome
COMPONENT_VERSION =		1.2.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		outcome - Capture the outcome of Python function calls.
COMPONENT_PROJECT_URL =		https://github.com/python-trio/outcome
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/dd/91/741e1626e89fdc3664169e16300c59eefa4b23540cc6d6c70450f885098f/outcome-1.2.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:6f82bd3de45da303cf1f771ecafa1633750a358436a8bb60e06a1ceb745d2672
COMPONENT_LICENSE =		Apache-2.0 OR MIT

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# The outcome module is needed during tests
COMPONENT_TEST_ENV += PYTHONPATH=$(@D)/src
COMPONENT_TEST_ENV += TOX_TESTENV_PASSENV=PYTHONPATH

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/attrs
PYTHON_REQUIRED_PACKAGES += runtime/python
