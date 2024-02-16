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
#   $WS_TOOLS/python-integrate-project pipdeptree
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pipdeptree
HUMAN_VERSION =			2.14.0
COMPONENT_SUMMARY =		pipdeptree - Command line utility to show dependency tree of packages.
COMPONENT_PROJECT_URL =		https://github.com/tox-dev/pipdeptree
COMPONENT_ARCHIVE_HASH =	\
	sha256:3296195250e00d37638f2cce70495e3345645b4bbecc1c38ac39339f1511d9b5
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/covdefaults
TEST_REQUIRED_PACKAGES.python += library/python/graphviz
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
