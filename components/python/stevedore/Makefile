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
HUMAN_VERSION =			5.0.0
COMPONENT_SUMMARY =		stevedore - Manage dynamic plugins for Python applications
COMPONENT_PROJECT_URL =		https://docs.openstack.org/stevedore/latest/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/f1/25/993d09dc7be3e7927228853c75324104d734bb784bd766b025ebf9f47b16/stevedore-5.0.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:2c428d2338976279e8eb2196f7a94910960d9f7ba2f41f3988511e95ca447021
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# stevedore >= 4.0.0 requires Python >= 3.8
PYTHON_VERSIONS := $(filter-out 3.7, $(PYTHON_VERSIONS))

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
