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
# Copyright 2012 Gary Mills
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=32_and_64
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pycups
COMPONENT_VERSION=	1.9.74
COMPONENT_PROJECT_URL=	http://cyberelk.net/tim/software/pycups/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:d5b5e4058757d1c090c85ed2ee7e5c2c1785976dc934a6144dbf425398304850
COMPONENT_ARCHIVE_URL=	https://github.com/OpenPrinting/pycups/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_BUGDB=	python-mod/pycups

PYTHON_VERSIONS=2.7 3.5

TEST_TARGET=$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# pycups requires VERSION to be defined. Originally set in the package Makefile
CFLAGS += -DVERSION=\\\"$(COMPONENT_VERSION)\\\"

REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
