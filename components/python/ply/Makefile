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
# Copyright 2017 Gary Mills
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ply
COMPONENT_VERSION=	3.8
COMPONENT_REVISION=	5
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e7d1bdff026beb159c9942f7a17e102c375638d9478a7ecd4cc0c76afd8de0b8
COMPONENT_ARCHIVE_URL=	http://www.dabeaz.com/ply/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.dabeaz.com/ply/
COMPONENT_BUGDB=	python-mod/ply

PYTHON_VERSIONS=	$(PYTHON_VERSIONS_ALL)

include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Run 42 tests, OK.
COMPONENT_TEST_ENV = PYTHONPATH=$(PROTO_DIR)/$(PYTHON_LIB)
COMPONENT_TEST_CMD = $(PYTHON) testlex.py; \
                     $(PYTHON) testyacc.py
COMPONENT_TEST_ARGS=
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
    '-e "s|\(^Ran 42 tests\).*|\1|" '


# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
