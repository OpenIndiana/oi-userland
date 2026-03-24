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
#   $WS_TOOLS/python-integrate-project -d python/python-subunit python_subunit
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		python_subunit
HUMAN_VERSION =			1.4.5
COMPONENT_SUMMARY =		Python implementation of subunit test streaming protocol
COMPONENT_PROJECT_URL =		http://launchpad.net/subunit
COMPONENT_ARCHIVE_URL =		\
	https://github.com/testing-cabal/subunit/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:c55b39d0802ca15c18fbf267faf3a1cf67b4fe2482abbb00755c31b53c833bf7
COMPONENT_LICENSE =		(Apache-2.0 OR BSD-3-Clause) AND MIT
COMPONENT_LICENSE_FILE =	COPYING

COMPONENT_SRC =			subunit-$(HUMAN_VERSION)

# https://bugs.launchpad.net/subunit/+bug/2046453/comments/2
TEST_STYLE = unittest

# Python 3.9 is not supported by python-subunit >= 1.4.5
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# https://bugs.launchpad.net/subunit/+bug/2046453/comments/2
COMPONENT_TEST_TARGETS += all_tests.test_suite
# The SHELL_SHARE is needed so testing is able to find subunit.sh
COMPONENT_TEST_ENV += SHELL_SHARE=$(@D)/shell/share/
# Testing expects this file executable
COMPONENT_PRE_TEST_ACTION += $(CHMOD) +x $(PROTOPYTHONVENDORDIR)/subunit/tests/sample-script.py

# Random temporary file name
COMPONENT_TEST_TRANSFORMS += "-e 's|\(/tmp/tmp\)[_a-z0-9]\{8\}|\1XXXXXXXX|'"

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += test

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/iso8601
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/testtools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/fixtures
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/testscenarios
