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
#   $WS_TOOLS/python-integrate-project pbr
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pbr
COMPONENT_VERSION =		5.11.0
COMPONENT_SUMMARY =		pbr - Python Build Reasonableness
COMPONENT_PROJECT_URL =		https://docs.openstack.org/pbr/latest/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/52/fb/630d52aaca8fc7634a0711b6ae12a0e828b6f9264bd8051225025c3ed075/pbr-5.11.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:b97bc6695b2aff02144133c2e7399d5885223d42b7912ffaec2ca3898e673bfe
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# pbr needs fixtures to run tests, but fixtures needs pbr to build itself.
# This is special case when we need to set PYTHON_TEST_BOOTSTRAP to make sure
# the pbr tests are not run when there is no fixtures available yet.
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/fixtures
TEST_REQUIRED_PACKAGES.python += library/python/hacking
TEST_REQUIRED_PACKAGES.python += library/python/mock
TEST_REQUIRED_PACKAGES.python += library/python/pre-commit
TEST_REQUIRED_PACKAGES.python += library/python/six
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/stestr
TEST_REQUIRED_PACKAGES.python += library/python/testrepository
TEST_REQUIRED_PACKAGES.python += library/python/testresources
TEST_REQUIRED_PACKAGES.python += library/python/testscenarios
TEST_REQUIRED_PACKAGES.python += library/python/testtools
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
TEST_REQUIRED_PACKAGES.python += library/python/wheel
