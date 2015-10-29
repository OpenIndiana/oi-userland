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
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cssutils
COMPONENT_VERSION=	0.9.6
COMPONENT_PROJECT_URL=	https://pypi.python.org/pypi/cssutils/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH= \
    sha256:18f3cffb2ff413e0796d0c9192db3a56f18fe57524cc54edc57d20239614eb87
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/source/c/cssutils/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/cssutils

TPNO=			7908

# This module is not Python 3 ready: syntax issues.
PYTHON_VERSIONS = $(PYTHON2_VERSIONS)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_TEST_DIR= $(COMPONENT_SRC)
COMPONENT_TEST_ARGS= ./setup.py test

# Remove the trailing Control-M's from the Python source files.
COMPONENT_PRE_BUILD_ACTION = \
	/usr/bin/find $(SOURCE_DIR)/src \
		-name *.py -exec $(GSED) -i -e 's///g' "{}" \; ;

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

build:          $(BUILD_NO_ARCH)

install:        $(INSTALL_NO_ARCH)

test:           $(TEST_NO_ARCH)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)
