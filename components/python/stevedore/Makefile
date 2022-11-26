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
#   $WS_TOOLS/python-integrate-project stevedore
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		stevedore
COMPONENT_VERSION =		4.1.1
COMPONENT_SUMMARY =		stevedore - Manage dynamic plugins for Python applications
COMPONENT_PROJECT_URL =		https://docs.openstack.org/stevedore/latest/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/66/c0/26afabea111a642f33cfd15f54b3dbe9334679294ad5c0423c556b75eba2/stevedore-4.1.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:7f8aeb6e3f90f96832c301bff21a7eb5eefbe894c88c506483d355565d88cc1a
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# stevedore --> bandit ==> stevedore
# stevedore --> stestr ==> cliff ==> stevedore
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pbr
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/bandit
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/pbr
TEST_REQUIRED_PACKAGES.python += library/python/pre-commit
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/stestr
