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
#   $WS_TOOLS/python-integrate-project keyrings.alt
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		keyrings.alt
HUMAN_VERSION =			5.0.0
COMPONENT_SUMMARY =		keyrings.alt - Alternate keyring implementations
COMPONENT_PROJECT_URL =		https://github.com/jaraco/keyrings.alt
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/a6/97/c7344bed881cc6f78b6231262436eb0c72615011fab4786d23d676ab77b0/keyrings.alt-5.0.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:9d446cb47bbcea90ffa2ecc3e8003acf41573fc201bf44b4bf13bd0e11484828
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# keyrings.alt --> keyring --> keyrings.alt
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-classes
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/backports-unittest-mock
TEST_REQUIRED_PACKAGES.python += library/python/keyring
TEST_REQUIRED_PACKAGES.python += library/python/pycryptodome
TEST_REQUIRED_PACKAGES.python += library/python/pycryptodomex
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-black
TEST_REQUIRED_PACKAGES.python += library/python/pytest-checkdocs
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-enabler
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
