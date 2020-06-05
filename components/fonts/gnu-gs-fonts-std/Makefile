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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gnu-gs-fonts-std
COMPONENT_VERSION=      6.0
COMPONENT_PROJECT_URL=	http://sourceforge.net/projects/gs-fonts/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:4cef38d05aa958dfee4dabb8d1599b8ad2b2347413b7895c94d8882c8a0fb9d3
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)files/gs-fonts/6.0%20%28base%2035%2C%20GPL%29/$(COMPONENT_ARCHIVE)/download
COMPONENT_BUGDB=	utility/ghostscript

# set relocate_to option while unpacking the tar ball
UNPACK_ARGS= -r $(COMPONENT_SRC)

PROTOGSSHAREDIR=$(PROTOUSRSHAREDIR)/ghostscript

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk

# untar the tar ball and apply the patches
build:  $(SOURCE_DIR)/.prep

install: build
	$(MKDIR) $(PROTO_DIR)
	$(MKDIR) -m 755 -p $(PROTOGSSHAREDIR)
	$(CP) -r $(SOURCE_DIR)/* $(PROTOGSSHAREDIR)

test:	$(NO_TESTS)

clean::
	$(RM) -r $(BUILD_DIR)
