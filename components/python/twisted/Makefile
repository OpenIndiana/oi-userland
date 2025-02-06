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
#   $WS_TOOLS/python-integrate-project twisted
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		twisted
HUMAN_VERSION =			24.11.0
COMPONENT_SUMMARY =		An asynchronous networking framework written in Python
COMPONENT_PROJECT_URL =		https://twisted.org/
COMPONENT_ARCHIVE_HASH =	\
	sha256:695d0556d5ec579dcc464d2856b634880ed1319f45b10d19043f2b57eb0115b5
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Testing fails with coverage-enable-subprocess installed
TEST_CONFLICTING_PACKAGES.python += library/python/coverage-enable-subprocess

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/attrs
PYTHON_REQUIRED_PACKAGES += library/python/automat
PYTHON_REQUIRED_PACKAGES += library/python/constantly
PYTHON_REQUIRED_PACKAGES += library/python/hatch-fancy-pypi-readme
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/hyperlink
PYTHON_REQUIRED_PACKAGES += library/python/incremental
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += library/python/zope-interface
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/cython-test-exception-raiser
TEST_REQUIRED_PACKAGES.python += library/python/h2
TEST_REQUIRED_PACKAGES.python += library/python/httpx
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/pyhamcrest
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
