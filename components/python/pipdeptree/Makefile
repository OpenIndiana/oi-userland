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
HUMAN_VERSION =			2.13.1
COMPONENT_SUMMARY =		pipdeptree - Command line utility to show dependency tree of packages.
COMPONENT_PROJECT_URL =		https://github.com/tox-dev/pipdeptree
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/b5/82/127215bd6bf6f1c0d98c89052eb91c67e34258b743395e3ebd24bc7a3816/pipdeptree-2.13.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:1e1acdb2ddc2abdca1718f27ca8dc21622c896a00b8980ec3d42c2208a841a10
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
