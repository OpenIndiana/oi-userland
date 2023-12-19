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
#   $WS_TOOLS/python-integrate-project Chameleon
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Chameleon
HUMAN_VERSION =			4.4.2
COMPONENT_SUMMARY =		Chameleon - Fast HTML/XML Template Compiler.
COMPONENT_PROJECT_URL =		https://chameleon.readthedocs.io
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/52/8f/261cd770dadb6cd01482c65ed6733f6627dafea3e8ec06d346e1bcd5dca7/Chameleon-4.4.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:b826dd5cc1327acdbd57a08db0bd5d8f549aa750cf38232a120f378394574987
COMPONENT_LICENSE =		BSD-3-Clause OR PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# Normalize timetstamps that change with every run
COMPONENT_TEST_TRANSFORMS += "-e 's|\[../../.. ..:..:..\]|[XX/XX/XX XX:XX:XX]|'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/build
TEST_REQUIRED_PACKAGES.python += library/python/wheel
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
