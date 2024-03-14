#
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
# Copyright (c) 2011, 2021, Oracle and/or its affiliates.
#

BUILD_BITS= NO_ARCH
BUILD_STYLE= archive
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gnu-gs-fonts-std
COMPONENT_VERSION=      8.11
COMPONENT_SUMMARY=		GNU Ghostscript Fonts (Standard)
COMPONENT_PROJECT_URL=	https://sourceforge.net/projects/gs-fonts
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:0eb6f356119f2e49b2563210852e17f57f9dcc5755f350a69a46a0d641a0c401
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/files/gs-fonts/8.11%20%28base%2035%2C%20GPL%29/ghostscript-fonts-std-8.11.tar.gz/download
COMPONENT_FMRI=			print/filter/ghostscript/fonts/gnu-gs-fonts-std
COMPONENT_CLASSIFICATION= System/Printing
COMPONENT_LICENSE=		GPLv2
COMPONENT_LICENSE_FILE=	fonts/COPYING

# set relocate_to option while unpacking the tar ball
UNPACK_ARGS= -r $(COMPONENT_SRC)

PROTOGSSHAREDIR=$(PROTOUSRSHAREDIR)/ghostscript

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# untar the tar ball and apply the patches
build:  $(SOURCE_DIR)/.prep

install: build
	$(MKDIR) $(PROTO_DIR)
	$(MKDIR) -m 755 -p $(PROTOGSSHAREDIR)
	$(CP) -r $(SOURCE_DIR)/* $(PROTOGSSHAREDIR)

clean::
	$(RM) -r $(BUILD_DIR)

# Auto-generated dependencies
