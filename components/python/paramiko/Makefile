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
#   $WS_TOOLS/python-integrate-project paramiko
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		paramiko
HUMAN_VERSION =			3.4.0
COMPONENT_SUMMARY =		paramiko - SSH2 protocol library
COMPONENT_PROJECT_URL =		https://paramiko.org
COMPONENT_ARCHIVE_URL =		\
	https://github.com/paramiko/paramiko/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:36a34a9bd0b1f4fca89c0d880fad7af69f4dc5f8f0fb8c795938bdf880694c1f
COMPONENT_LICENSE =		LGPL-2.1-only
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += dev-requirements.txt

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/bcrypt
PYTHON_REQUIRED_PACKAGES += library/python/cryptography
PYTHON_REQUIRED_PACKAGES += library/python/pynacl
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/alabaster
TEST_REQUIRED_PACKAGES.python += library/python/black
TEST_REQUIRED_PACKAGES.python += library/python/codespell
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/icecream
TEST_REQUIRED_PACKAGES.python += library/python/invocations
TEST_REQUIRED_PACKAGES.python += library/python/invoke
TEST_REQUIRED_PACKAGES.python += library/python/pytest-relaxed
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/releases
TEST_REQUIRED_PACKAGES.python += library/python/watchdog
