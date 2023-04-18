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
#   $WS_TOOLS/python-integrate-project cliff
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cliff
HUMAN_VERSION =			3.10.1
COMPONENT_SUMMARY =		cliff - Command Line Interface Formulation Framework
COMPONENT_PROJECT_URL =		https://docs.openstack.org/cliff/latest/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/71/33/0115d1f56dce6bc9f4f4b394347c52a7182109026d2c25d8837047e3edee/cliff-3.10.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:045aee3f3c64471965d7ad507ce8474a4e2f20815fbb5405a770f8596a2a00a0
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# cliff >= 4.0.0 requires Python >= 3.8
PYTHON_VERSIONS = 3.7

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# cliff --> stestr ==> cliff
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/autopage
PYTHON_REQUIRED_PACKAGES += library/python/cmd2
PYTHON_REQUIRED_PACKAGES += library/python/pbr
PYTHON_REQUIRED_PACKAGES += library/python/prettytable
PYTHON_REQUIRED_PACKAGES += library/python/pyparsing
PYTHON_REQUIRED_PACKAGES += library/python/pyyaml
PYTHON_REQUIRED_PACKAGES += library/python/stevedore
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/autopage
TEST_REQUIRED_PACKAGES.python += library/python/bandit
TEST_REQUIRED_PACKAGES.python += library/python/cmd2
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/pbr
TEST_REQUIRED_PACKAGES.python += library/python/prettytable
TEST_REQUIRED_PACKAGES.python += library/python/pyparsing
TEST_REQUIRED_PACKAGES.python += library/python/python-subunit
TEST_REQUIRED_PACKAGES.python += library/python/pyyaml
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/stestr
TEST_REQUIRED_PACKAGES.python += library/python/stevedore
TEST_REQUIRED_PACKAGES.python += library/python/testscenarios
TEST_REQUIRED_PACKAGES.python += library/python/testtools
