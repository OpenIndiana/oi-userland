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
HUMAN_VERSION =			3.5.2
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		stevedore - Manage dynamic plugins for Python applications
COMPONENT_PROJECT_URL =		https://docs.openstack.org/stevedore/latest/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/80/a3/7db17f998684ee1c225cfae74ccca4b369118419c07be48991f30e942c31/stevedore-3.5.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:cf99f41fc0d5a4f185ca4d3d42b03be9011b0a1ec1a4ea1a282be1b4b306dcc2
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# stevedore-4.1.1 was mistakenly packaged for Python 3.7
COMPONENT_VERSION =		4.1.1

# stevedore >= 4.0.0 requires Python >= 3.8
PYTHON_VERSIONS = 3.7

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
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/pbr
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/bandit
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/importlib-metadata
TEST_REQUIRED_PACKAGES.python += library/python/pbr
TEST_REQUIRED_PACKAGES.python += library/python/pre-commit
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/stestr
