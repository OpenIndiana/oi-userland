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
HUMAN_VERSION =			2.4.3
COMPONENT_SUMMARY =		Fix common misspellings in text files
COMPONENT_PROJECT_URL =		https://github.com/codespell-project/codespell
COMPONENT_ARCHIVE_HASH =	\
	sha256:cbe085e331227b37bb86ef8bddd08dc768c704ee9a07ca869852c093fa2793e2
COMPONENT_LICENSE =		GPL-2.0-only
COMPONENT_LICENSE_FILE =	COPYING

include $(WS_MAKE_RULES)/common.mk

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/build
TEST_REQUIRED_PACKAGES.python += library/python/chardet
TEST_REQUIRED_PACKAGES.python += library/python/pygments
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/tomli
