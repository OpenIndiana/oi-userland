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
#   $WS_TOOLS/python-integrate-project poetry-core
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		poetry-core
COMPONENT_VERSION =		1.3.2
COMPONENT_SUMMARY =		poetry-core - Poetry PEP 517 Build Backend
COMPONENT_PROJECT_URL =		https://github.com/python-poetry/poetry-core
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/0d/07/2a30643e4177c8edafa037c8ee3c62e4390950ab01d5ebc86e04379e2ba7/poetry-core-1.3.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:0ab006a40cb38d6a38b97264f6835da2f08a96912f2728ce668e9ac6a34f686f
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# poetry-core needs poetry to run tests, but poetry needs poetry-core to build
# itself.  This is special case when we need to set PYTHON_TEST_BOOTSTRAP to
# make sure the poetry-core tests are not run when there is no poetry available
# yet.
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += runtime/python
