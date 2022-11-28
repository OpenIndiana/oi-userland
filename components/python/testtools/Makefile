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

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		testtools
COMPONENT_VERSION =		2.5.0
COMPONENT_SUMMARY =		testtools - Extensions to the Python standard library unit testing framework
COMPONENT_PROJECT_URL =		https://github.com/testing-cabal/testtools
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/29/0f/99dbb1801e341d74cd74e493906a16d8ddffffa86879d90ac3dc1f367b13/testtools-2.5.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:57c13433d94f9ffde3be6534177d10fb0c1507cc499319128958ca91a65cb23f
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

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/extras
PYTHON_REQUIRED_PACKAGES += library/python/fixtures
PYTHON_REQUIRED_PACKAGES += library/python/pbr
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/testresources
TEST_REQUIRED_PACKAGES.python += library/python/testscenarios
TEST_REQUIRED_PACKAGES.python += library/python/twisted
