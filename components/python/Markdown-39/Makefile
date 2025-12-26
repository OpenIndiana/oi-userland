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
#   $WS_TOOLS/python-integrate-project -d python/Markdown-39 markdown
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		markdown
HUMAN_VERSION =			3.9
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Python implementation of John Gruber's Markdown.
COMPONENT_PROJECT_URL =		https://Python-Markdown.github.io/
COMPONENT_ARCHIVE_HASH =	\
	sha256:d2900fe1782bd33bdbbd56859defef70c2e78fc46668f8eb9df3128138f2cb6a
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.md

# Markdown >= 3.10 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/importlib-metadata
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytidylib
TEST_REQUIRED_PACKAGES.python += library/python/pyyaml
