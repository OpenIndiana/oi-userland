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
#   $WS_TOOLS/python-integrate-project lxml_html_clean
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		lxml_html_clean
HUMAN_VERSION =			0.4.5
COMPONENT_SUMMARY =		HTML cleaner from lxml project
COMPONENT_PROJECT_URL =		https://github.com/fedora-python/lxml_html_clean/
COMPONENT_ARCHIVE_HASH =	\
	sha256:e2a4c7d5beedd17cd7b484d848a0571e54baa239a4f9df5546e3acba7f990560
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Testing needs to find the tests module in the build directory
COMPONENT_TEST_ENV += PYTHONPATH=$(PROTOPYTHONVENDORDIR):$(COMPONENT_TEST_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/lxml
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/lxml
