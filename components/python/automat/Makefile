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
# Copyright (c) 2019, Oracle and/or its affiliates. All rights reserved.
#

BUILD_STYLE=setup.py
BUILD_BITS=NO_ARCH
PYTHON3_ONLY=yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         Automat
COMPONENT_VERSION=      20.2.0
COMPONENT_SUMMARY=      'Self-service finite-state machines for the programmer on the go'
COMPONENT_DESCRIPTION=	'Automat is a library for concise, idiomatic Python expression of finite-state automata (particularly deterministic finite-state transducers)'
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:7979803c74610e11ef0c0d68a2942b152df52da55336e0c9d58daf1831cbdf33
COMPONENT_ARCHIVE_URL=  $(call pypi_url)
COMPONENT_PROJECT_URL=  https://github.com/glyph/Automat
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_FMRI=         library/python/automat
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

# make executable for each Python version
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(PROTOUSRBINDIR)/automat-visualize $(PROTOUSRBINDIR)/automat-visualize-$(PYTHON_VERSION)

COMPONENT_TEST_DIR =	$(SOURCE_DIR)/automat
COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =

COMPONENT_TEST_TRANSFORMS= '-n' '-e "/^_test/p"'

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
