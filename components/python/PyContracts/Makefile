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
#   $WS_TOOLS/python-integrate-project PyContracts
#

BUILD_STYLE = setup.py
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		PyContracts
COMPONENT_VERSION =		1.8.12
COMPONENT_SUMMARY =		PyContracts - PyContracts is a Python package that allows to declare constraints on function parameters and return values. Contracts can be specified using Python3 annotations, in a decorator, or inside a docstring :type: and :rtype: tags. PyContracts supports a basic type system, variables binding, arithmetic constraints, and has several specialized contracts (notably for Numpy arrays), as well as an extension API.
COMPONENT_PROJECT_URL =		http://andreacensi.github.com/contracts/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/4e/7a/0f79370e4e3a6741396d76d1f76586c2924bed049fb38597799b72a24081/PyContracts-1.8.12.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:5cab6ea60efb4ed66a46e4e962897a4a57d1180a9cf08d701d639884f33326b7
COMPONENT_LICENSE =		LGPL-3.0-only
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

# This project no longer publish releases at PyPI
# https://github.com/AndreaCensi/contracts/issues/86
# https://github.com/AndreaCensi/contracts/issues/90
# https://github.com/AndreaCensi/contracts/issues/92
COMPONENT_VERSION = 2.0.1
COMPONENT_ARCHIVE_URL = https://github.com/AndreaCensi/contracts/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_SRC = contracts-$(COMPONENT_VERSION)

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/decorator
PYTHON_REQUIRED_PACKAGES += library/python/future
PYTHON_REQUIRED_PACKAGES += library/python/pyparsing
PYTHON_REQUIRED_PACKAGES += library/python/six
PYTHON_REQUIRED_PACKAGES += runtime/python
