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
#   $WS_TOOLS/python-integrate-project -d python/Markdown markdown
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		markdown
HUMAN_VERSION =			3.10.3
COMPONENT_SUMMARY =		Python implementation of John Gruber's Markdown.
COMPONENT_PROJECT_URL =		https://Python-Markdown.github.io/
COMPONENT_ARCHIVE_HASH =	\
	sha256:3589362618f743188b4d955b874402bc814f4f83f544dc207719f4baa7d9c45f
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.md

# Python 3.9 is not supported by Markdown >= 3.10
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytidylib
TEST_REQUIRED_PACKAGES.python += library/python/pyyaml
