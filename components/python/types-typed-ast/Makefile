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
#   $WS_TOOLS/python-integrate-project types-typed-ast
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		types-typed-ast
HUMAN_VERSION =			1.5.8.7
COMPONENT_SUMMARY =		types-typed-ast - Typing stubs for typed-ast
COMPONENT_PROJECT_URL =		https://github.com/python/typeshed
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/dc/44/2b4c6b15bf901533966f63ca5b073e4f9b7a9532bb4a64d9ceb83432db9b/types-typed-ast-1.5.8.7.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f7795f6f9d597b35212314040b993f6613b51d81738edce3c1e3a3e9ef655124
COMPONENT_LICENSE =		Apache-2.0 AND MIT

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# We are not interested in coverage reports
PYTEST_ADDOPTS += -p no:cov
# https://github.com/python/typeshed/issues/10386
PYTEST_ADDOPTS += -p no:black

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
