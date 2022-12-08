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
#   $WS_TOOLS/python-integrate-project cffi
#

BUILD_STYLE = setup.py
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cffi
HUMAN_VERSION =			1.15.1
COMPONENT_SUMMARY =		cffi - Foreign Function Interface for Python calling C code.
COMPONENT_PROJECT_URL =		http://cffi.readthedocs.org
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/2b/a8/050ab4f0c3d4c1b8aaa805f70e26e84d0e27004907c5b8ecc1d31815f92a/cffi-1.15.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:d400bfb9a37b1351253cb402671cea7e89bdecc294e8016a707f6d1d8ac934f9
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Set full path to gcc for testing
COMPONENT_PREP_ACTION = $(GSED) -i -e 's|cc|'"$(CC.$(COMPILER).$(BUILD_BITS))"'|' $(@D)/testing/cffi0/test_ownlib.py

# Without this some random tests could fail
PYTEST_ADDOPTS += -p no:randomly

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pycparser
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += system/library
