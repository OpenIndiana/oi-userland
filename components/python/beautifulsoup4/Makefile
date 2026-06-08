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
#   $WS_TOOLS/python-integrate-project beautifulsoup4
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		beautifulsoup4
HUMAN_VERSION =			4.15.0
COMPONENT_SUMMARY =		Screen-scraping library
COMPONENT_PROJECT_URL =		https://www.crummy.com/software/BeautifulSoup/bs4/
COMPONENT_ARCHIVE_HASH =	\
	sha256:288e3ca7d54b06f2ac191970bc275c1939cb46d450b255bf6718b04aa37ab4f7
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Test results order varies between runs
PYTEST_SORT_TESTS = yes

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += library/python/soupsieve
REQUIRED_PACKAGES.python += library/python/typing-extensions
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/lxml
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/soupsieve
TEST_REQUIRED_PACKAGES.python += library/python/typing-extensions
