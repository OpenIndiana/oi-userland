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
#   $WS_TOOLS/python-integrate-project cmarkgfm
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cmarkgfm
HUMAN_VERSION =			2025.10.22
COMPONENT_SUMMARY =		Minimal bindings to GitHub's fork of cmark
COMPONENT_PROJECT_URL =		https://github.com/theacodes/cmarkgfm
COMPONENT_ARCHIVE_HASH =	\
	sha256:5bec61007b65b919488442c838c58a6c8bf4741f5103c593b2ef180d39818eda
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Needed to get strncasecmp() declaration
CFLAGS += $(XPG5MODE)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/cffi
REQUIRED_PACKAGES.python += library/python/pycparser
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
