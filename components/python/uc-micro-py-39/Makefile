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
#   $WS_TOOLS/python-integrate-project -d python/uc-micro-py-39 uc-micro-py
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		uc-micro-py
HUMAN_VERSION =			1.0.3
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Micro subset of unicode data files for linkify-it-py projects.
COMPONENT_PROJECT_URL =		https://github.com/tsutsu3/uc.micro-py
COMPONENT_ARCHIVE_HASH =	\
	sha256:d321b92cff673ec58027c04015fcaa8bb1e005478643ff4a500882eaab88c48a
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# uc-micro-py >= 2.0.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
