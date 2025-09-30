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
#   $WS_TOOLS/python-integrate-project cheroot
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cheroot
HUMAN_VERSION =			11.0.0
COMPONENT_SUMMARY =		Highly-optimized, pure-python HTTP server
COMPONENT_PROJECT_URL =		https://cheroot.cherrypy.dev
COMPONENT_ARCHIVE_HASH =	\
	sha256:dd414eda6bdb15140e864bc1d1c9625030375d14cbe0b290092867368924a52f
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.md

include $(WS_MAKE_RULES)/common.mk

# Avoid rewrite failure with xdist
PYTEST_ADDOPTS += --assert=plain

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/jaraco-functools
REQUIRED_PACKAGES.python += library/python/more-itertools
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/chardet
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-context
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-text
TEST_REQUIRED_PACKAGES.python += library/python/portend
TEST_REQUIRED_PACKAGES.python += library/python/pyopenssl
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest-rerunfailures
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/requests
TEST_REQUIRED_PACKAGES.python += library/python/requests-toolbelt
TEST_REQUIRED_PACKAGES.python += library/python/trustme
