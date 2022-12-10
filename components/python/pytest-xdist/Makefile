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
#   $WS_TOOLS/python-integrate-project pytest-xdist
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest-xdist
COMPONENT_VERSION =		3.1.0
COMPONENT_SUMMARY =		pytest-xdist - pytest xdist plugin for distributed testing, most importantly across multiple CPUs
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-xdist
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/0d/e5/f7ece02dc1b4bc24a3e37be6a78251e03fff4193126d7ce126c450644696/pytest-xdist-3.1.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:40fdb8f3544921c5dfcd486ac080ce22870e71d82ced6d2e78fa97c2addd480c
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# There is an incompatibility between execnet and teamcity-messages causing
# some tests to fail if teamcity-messages is installed while pytest-xdist tests
# are run.  See https://github.com/pytest-dev/execnet/issues/161 for details.
#
# Testing of pytest-xdist fails if there is pytest-randomly installed.  See
# https://github.com/pytest-dev/pytest-xdist/issues/742 for details.
#
# To see pytest-xdist tests to pass the teamcity-messages and pytest-randomly
# packages should NOT be installed during testing.

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/execnet
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/filelock
