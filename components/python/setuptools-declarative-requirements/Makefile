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
#   $WS_TOOLS/python-integrate-project setuptools-declarative-requirements
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		setuptools-declarative-requirements
HUMAN_VERSION =			1.3.0
COMPONENT_SUMMARY =		setuptools-declarative-requirements - File support for setuptools declarative setup.cfg
COMPONENT_PROJECT_URL =		https://github.com/s0undt3ch/setuptools-declarative-requirements
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/f0/06/85fb4a4ccb82f5040cd5ddc4ab55db5f9d16e0a1b43887e82a8e671e17cb/setuptools-declarative-requirements-1.3.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:57a5b9bb9ad350c278e8aa6be4cdebbcd925b9ba71d6a712a178a618cfb898f7
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# setuptools-declarative-requirements --> pytest-shell-utilities ==> setuptools-declarative-requirements
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += requirements/tests.in

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pypiserver
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-shell-utilities
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
