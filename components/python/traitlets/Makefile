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
HUMAN_VERSION =			5.14.0
COMPONENT_SUMMARY =		traitlets - Traitlets Python configuration system
COMPONENT_PROJECT_URL =		https://github.com/ipython/traitlets
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/25/a0/2feefaa884a7eaa83934476091ecfb2a3bc3b61c1ed98db3da0fbbf46e73/traitlets-5.14.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:fcdaa8ac49c04dfa0ed3ee3384ef6dfdb5d6f3741502be247279407679296772
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
