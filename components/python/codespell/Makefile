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
HUMAN_VERSION =			2.2.6
COMPONENT_SUMMARY =		codespell - Codespell
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/e1/97/df3e00b4d795c96233e35d269c211131c5572503d2270afb6fed7d859cc2/codespell-2.2.6.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:a8c65d8eb3faa03deabab6b3bbe798bea72e1799c7e9e955d57eca4096abcff9
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
