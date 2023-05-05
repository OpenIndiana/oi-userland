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
#   $WS_TOOLS/python-integrate-project lxml-stubs
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		lxml-stubs
HUMAN_VERSION =			0.4.0
COMPONENT_SUMMARY =		lxml-stubs - Type annotations for the lxml package
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/0d/2f/9e1ce676e94fe929c668b20cc1a761fb26cb4654b7e7fb965da50a105212/lxml-stubs-0.4.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:1e464c16421d7607ccebaf3e876247e82b8362fccc7f38a0245397449281d05e
COMPONENT_LICENSE =		Apache-2.0 OR MIT
COMPONENT_LICENSE_FILE =	LICENSE

# https://github.com/lxml/lxml-stubs/issues/90
COMPONENT_ARCHIVE_URL =		\
	https://github.com/lxml/lxml-stubs/archive/refs/tags/$(HUMAN_VERSION).tar.gz

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy-plugins
