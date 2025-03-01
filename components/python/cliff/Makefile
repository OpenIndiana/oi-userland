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

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cliff
HUMAN_VERSION =			4.9.1
COMPONENT_SUMMARY =		Command Line Interface Formulation Framework
COMPONENT_PROJECT_URL =		https://docs.openstack.org/cliff/latest/
COMPONENT_ARCHIVE_HASH =	\
	sha256:5b392198293c0b9225d459be8ba710cf8248f1ee33006bdeb3d92fb0012592b4
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

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

# Ignore stdout and stderr of successfull tests
TOX_POSARGS += --suppress-attachments

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/autopage
PYTHON_REQUIRED_PACKAGES += library/python/cmd2
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/pbr
PYTHON_REQUIRED_PACKAGES += library/python/prettytable
PYTHON_REQUIRED_PACKAGES += library/python/pyyaml
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/stevedore
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/autopage
TEST_REQUIRED_PACKAGES.python += library/python/cmd2
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/fixtures
TEST_REQUIRED_PACKAGES.python += library/python/importlib-metadata
TEST_REQUIRED_PACKAGES.python += library/python/prettytable
TEST_REQUIRED_PACKAGES.python += library/python/pyyaml
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/stestr
TEST_REQUIRED_PACKAGES.python += library/python/stevedore
TEST_REQUIRED_PACKAGES.python += library/python/testscenarios
TEST_REQUIRED_PACKAGES.python += library/python/testtools
