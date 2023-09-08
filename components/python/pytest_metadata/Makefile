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
#   $WS_TOOLS/python-integrate-project pytest_metadata
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest_metadata
HUMAN_VERSION =			3.0.0
COMPONENT_SUMMARY =		pytest_metadata - pytest plugin for test session metadata
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-metadata
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/fa/0a/2d380e69561a2fea3f395ef2504461cdb52387fba780d13796bfddc6a416/pytest_metadata-3.0.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:769a9c65d2884bd583bc626b0ace77ad15dbe02dd91a9106d47fd46d9c2569ca
COMPONENT_LICENSE =		MPL-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_TARGETS += --
# Force no colors via tox posargs to override defaults in tox.ini
COMPONENT_TEST_TARGETS += --color=no
# override -s in tox.ini to suppress annoying test output
COMPONENT_TEST_TARGETS += --capture=fd

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += runtime/python
