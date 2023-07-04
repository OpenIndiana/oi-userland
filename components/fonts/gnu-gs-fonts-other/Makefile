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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= NO_ARCH
BUILD_STYLE= archive
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gnu-gs-fonts-other
COMPONENT_VERSION=      6.0
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=		GNU Ghostscript Fonts (Other)
COMPONENT_PROJECT_URL=	https://sourceforge.net/projects/gs-fonts/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:8146cccc4699fe9dab841446bdd17039f4769c903eceb54409188b920754aab3
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)files/gs-fonts/6.0%20%28misc%2C%20GPL%29/$(COMPONENT_ARCHIVE)/download
COMPONENT_FMRI=			print/filter/ghostscript/fonts/gnu-gs-fonts-other
COMPONENT_CLASSIFICATION=	System/Printing
COMPONENT_LICENSE=		GPLv2

# set relocate_to option while unpacking the tar ball
UNPACK_ARGS= -r $(COMPONENT_SRC)

PROTOGSSHAREDIR= $(PROTOUSRSHAREDIR)/ghostscript

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# untar the tar ball and apply the patches
build:		$(SOURCE_DIR)/.prep

install: build
	$(MKDIR) $(PROTO_DIR)
	$(MKDIR) -m 755 -p $(PROTOGSSHAREDIR)
	$(CP) -r $(SOURCE_DIR)/* $(PROTOGSSHAREDIR)

clean::
	$(RM) -r $(BUILD_DIR)

