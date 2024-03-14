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
#   $WS_TOOLS/python-integrate-project lazy
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		lazy
HUMAN_VERSION =			1.6
COMPONENT_SUMMARY =		lazy - Lazy attributes for Python objects
COMPONENT_PROJECT_URL =		https://github.com/stefanholek/lazy
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/3c/e6/704c32da169b023a9ac86d116f5433b42d02b4afeda24c9400a69b3530e5/lazy-1.6.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:7127324ec709e8324f08cb4611c1abe01776bda53bb9ce68dc5dfa46ca0ed3e9
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Force verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -v

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
