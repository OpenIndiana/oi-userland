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
#   $WS_TOOLS/python-integrate-project cssselect
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cssselect
HUMAN_VERSION =			1.5.0
COMPONENT_SUMMARY =		cssselect parses CSS3 Selectors and translates them to XPath 1.0
COMPONENT_PROJECT_URL =		https://github.com/scrapy/cssselect
COMPONENT_ARCHIVE_HASH =	\
	sha256:3cbe82dd7acbee9ba9e5723b5f9e4749826912f1fb31cd7f92aabed5fde15b15
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

# Python 3.9 is not supported by cssselect >= 1.4.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/lxml
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/sybil
