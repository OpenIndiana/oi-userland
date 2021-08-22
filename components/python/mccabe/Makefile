#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright 2021 Gary Mills
#

BUILD_STYLE=	setup.py
BUILD_BITS=	NO_ARCH

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mccabe
COMPONENT_VERSION=	0.6.1
# COMPONENT_REVISION=	0
COMPONENT_PROJECT_URL=	https://github.com/PyCQA/mccabe
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:2748af6516175b94be318cd8226fa50b5339b9dc886bce378ac2afb37a157524
COMPONENT_ARCHIVE_URL=	https://github.com/PyCQA/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_BUGDB=	python-mod/mccabe

# Set python version used by this product
PYTHON_VERSION=		3.9
PYTHON_VERSIONS=	3.9

include $(WS_MAKE_RULES)/common.mk

# The tests are run using python 3.9 only and require that the
# python-39 package is installed (does not have to be the default python).
# The pytest-39 and hypothesis-39 packages must also be installed

# Use the python 3.9 libraries (via PYTHONPATH setting) for testing.
test: PYTHON_VERSION=3.9

COMPONENT_TEST_DIR = $(COMPONENT_SRC)
COMPONENT_TEST_CMD = $(PYTHON) -m pytest
COMPONENT_TEST_ARGS =

# Typical results for test target:
#collected 14 items
#test_mccabe.py ..............                                            [100%]
#============================== 14 passed in 0.07s =============================

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-39
