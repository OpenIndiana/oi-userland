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
#   $WS_TOOLS/python-integrate-project codespell
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		codespell
HUMAN_VERSION =			2.2.5
COMPONENT_SUMMARY =		codespell - Codespell
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/81/30/e1b32067c551d745df2bdc9f1d510422d8a5819ca3b610b4433654cf578c/codespell-2.2.5.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:6d9faddf6eedb692bf80c9a94ec13ab4f5fb585aabae5f3750727148d7b5be56
COMPONENT_LICENSE =		GPL-2.0-only
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Not sure how to detect this test dependency automatically (see pyproject.toml)
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
