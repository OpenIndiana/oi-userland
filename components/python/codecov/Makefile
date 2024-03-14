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
#   $WS_TOOLS/python-integrate-project codecov
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		codecov
HUMAN_VERSION =			2.1.13
COMPONENT_SUMMARY =		codecov - Hosted coverage reports for GitHub, Bitbucket and Gitlab
COMPONENT_PROJECT_URL =		https://github.com/codecov/codecov-python
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/2c/bb/594b26d2c85616be6195a64289c578662678afa4910cef2d3ce8417cf73e/codecov-2.1.13.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:2362b685633caeaf45b9951a9b76ce359cd3581dd515b430c6c3f5dfb4d92a8c
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# https://github.com/codecov/codecov-python/issues/324
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/coverage
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/requests
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
