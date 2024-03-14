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
#   $WS_TOOLS/python-integrate-project traitlets
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		traitlets
HUMAN_VERSION =			5.14.1
COMPONENT_SUMMARY =		traitlets - Traitlets Python configuration system
COMPONENT_PROJECT_URL =		https://github.com/ipython/traitlets
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/f1/b9/19206da568095bbf2e57f9f7f7cb6b3b2af2af2670f8c83c23a53d6c00cd/traitlets-5.14.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:8585105b371a04b8316a43d5ce29c098575c2e477850b62b848b964f1444527e
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += test

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/argcomplete
TEST_REQUIRED_PACKAGES.python += library/python/mypy
TEST_REQUIRED_PACKAGES.python += library/python/pre-commit
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
