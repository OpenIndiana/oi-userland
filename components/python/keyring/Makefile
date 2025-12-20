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
#   $WS_TOOLS/python-integrate-project keyring
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		keyring
HUMAN_VERSION =			25.7.0
COMPONENT_SUMMARY =		Store and access your passwords safely.
COMPONENT_ARCHIVE_HASH =	\
	sha256:fe01bd85eb3f8fb3dd0405defdeac9a5b4f6f0439edbb3149577f244a2e8245b
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# keyring --> keyrings.alt --> keyring
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# https://github.com/jaraco/keyring/issues/737
TEST_REQUIRED_PACKAGES.python += library/python/keyrings-alt

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/coherent-licensed
REQUIRED_PACKAGES.python += library/python/importlib-metadata
REQUIRED_PACKAGES.python += library/python/jaraco-classes
REQUIRED_PACKAGES.python += library/python/jaraco-context
REQUIRED_PACKAGES.python += library/python/jaraco-functools
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pyfakefs
TEST_REQUIRED_PACKAGES.python += library/python/pytest
