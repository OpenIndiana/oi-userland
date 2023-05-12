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
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pipdeptree
HUMAN_VERSION =			2.7.1
COMPONENT_SUMMARY =		pipdeptree - Command line utility to show dependency tree of packages.
COMPONENT_PROJECT_URL =		https://github.com/tox-dev/pipdeptree
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/b0/60/af20fcbf3cab57b63c5bad2ef25a037ade8af5084635b42d371189286316/pipdeptree-2.7.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:550bd7679379e7290739384f3e9518835620e814cc29ba709513952b627da506
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/covdefaults
TEST_REQUIRED_PACKAGES.python += library/python/diff-cover
TEST_REQUIRED_PACKAGES.python += library/python/graphviz
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
