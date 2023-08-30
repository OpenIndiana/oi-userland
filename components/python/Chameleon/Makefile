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
HUMAN_VERSION =			4.1.0
COMPONENT_SUMMARY =		Chameleon - Fast HTML/XML Template Compiler.
COMPONENT_PROJECT_URL =		https://chameleon.readthedocs.io
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/a6/b3/a12f28e3a0ed85d2b953ab67dcba7983e6f6aed9c74f4faee2551c71dd20/Chameleon-4.1.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f1a372a8ceb38690f96fe55c4e1b5aca76614c41042dd997668295059992b880
COMPONENT_LICENSE =		PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
