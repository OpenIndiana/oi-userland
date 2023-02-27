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
#   $WS_TOOLS/python-integrate-project wrapt
#

BUILD_STYLE = setup.py
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		wrapt
HUMAN_VERSION =			1.15.0
COMPONENT_SUMMARY =		wrapt - Module for decorators, wrappers and monkey patching.
COMPONENT_PROJECT_URL =		https://github.com/GrahamDumpleton/wrapt
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/f8/7d/73e4e3cdb2c780e13f9d87dc10488d7566d8fd77f8d68f0e416bfbd144c7/wrapt-1.15.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:d06730c6aed78cee4126234cf2d071e01b44b915e725a6cb439a879ec9754a3a
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# https://github.com/GrahamDumpleton/wrapt/issues/229
PYTEST_ADDOPTS += -p no:randomly

# Revert back unneeded PYV normalizations
COMPONENT_TEST_TRANSFORMS += "-e 's/\(test_class_py\)\$$(PYV)/\1$(shell echo $(PYTHON_VERSION) | tr -d .)/'"
COMPONENT_TEST_TRANSFORMS += "-e 's/\(test_inheritance_py\)\$$(PYV)/\1$(shell echo $(PYTHON_VERSION) | tr -d .)/'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/pytest
