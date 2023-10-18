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

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		outcome
HUMAN_VERSION =			1.3.0
COMPONENT_SUMMARY =		outcome - Capture the outcome of Python function calls.
COMPONENT_PROJECT_URL =		https://github.com/python-trio/outcome
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/64/1a/07e59b55f180506c72843d767a229c48084f5440005c646353742a4301bb/outcome-1.3.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:588ef4dc10b64e8df160d8d1310c44e1927129a66d6d2ef86845cef512c5f24c
COMPONENT_LICENSE =		Apache-2.0 OR MIT

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += test-requirements.txt

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/attrs
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-asyncio
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
