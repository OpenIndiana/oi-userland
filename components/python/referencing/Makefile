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
#   $WS_TOOLS/python-integrate-project referencing
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		referencing
HUMAN_VERSION =			0.31.0
COMPONENT_SUMMARY =		referencing - JSON Referencing + Python
COMPONENT_PROJECT_URL =		https://github.com/python-jsonschema/referencing
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/61/11/5e947c3f2a73e7fb77fd1c3370aa04e107f3c10ceef4880c2e25ef19679c/referencing-0.31.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:cc28f2c88fbe7b961a7817a0abc034c09a1e36358f82fedb4ffdf29a25398863
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += test-requirements.in

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/attrs
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/rpds-py
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-subtests
