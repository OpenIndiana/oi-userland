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
#   $WS_TOOLS/python-integrate-project graphviz
#

BUILD_STYLE = setup.py
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		graphviz
COMPONENT_VERSION =		0.20.1
COMPONENT_SUMMARY =		graphviz - Simple Python interface for Graphviz
COMPONENT_PROJECT_URL =		https://github.com/xflr6/graphviz
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/a5/90/fb047ce95c1eadde6ae78b3fca6a598b4c307277d4f8175d12b18b8f7321/graphviz-0.20.1.zip
COMPONENT_ARCHIVE_HASH =	\
	sha256:8c58f14adaa3b947daf26c19bc1e98c4e0702cdc31cf99153e6f06904d492bf8
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

COMPONENT_ARCHIVE =		$(COMPONENT_SRC).zip

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
