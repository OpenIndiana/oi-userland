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
#   $WS_TOOLS/python-integrate-project time-machine
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		time-machine
HUMAN_VERSION =			2.10.0
COMPONENT_SUMMARY =		time-machine - Travel through time in your tests.
COMPONENT_PROJECT_URL =		https://github.com/adamchainz/time-machine
COMPONENT_ARCHIVE_URL =		\
	https://github.com/adamchainz/time-machine/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:bfd7fcaa8e8888a8af423aa4a76d0930ac51ffa05e8e75590d9828d5d8e25623
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# https://github.com/adamchainz/time-machine/issues/360
PYTEST_ADDOPTS += -p no:mypy

# https://github.com/christiansandberg/pytest-reporter/issues/8
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-reporter

# Testing unable to start with pytest-black installed
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-black

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/python-dateutil
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
