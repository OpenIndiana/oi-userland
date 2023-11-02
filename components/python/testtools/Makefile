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
#   $WS_TOOLS/python-integrate-project testtools
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		testtools
HUMAN_VERSION =			2.7.0
COMPONENT_SUMMARY =		testtools - Extensions to the Python standard library unit testing framework
COMPONENT_PROJECT_URL =		https://github.com/testing-cabal/testtools
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/06/86/5f50ae3fbcd5035a15919854b2b6c6170628693dfd4e042064273c1f6d1a/testtools-2.7.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:eec326f4275e6a55e5540302d01a0ae0a9e48991d7aade38a5c8ed093c37993a
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# testtools --> testscenarios ==> testtools
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Normalize port
COMPONENT_TEST_TRANSFORMS += "-e 's/\(laddr=('\''127.0.0.1'\'', \)[0-9]\{1,\})/\1\$$(PORT))/'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/fixtures
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/setuptools-scm
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/testresources
TEST_REQUIRED_PACKAGES.python += library/python/testscenarios
TEST_REQUIRED_PACKAGES.python += library/python/twisted
