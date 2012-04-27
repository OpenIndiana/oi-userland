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

COMPONENT_NAME=		rds-tools
COMPONENT_VERSION=	2.0.4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:31b5924f73bed59e513470586c69ebe92eeb708fcc61a0519045fcf7954233a3
COMPONENT_ARCHIVE_URL=	http://www.openfabrics.org/downloads/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include ../ofed.mk

CPPFLAGS +=	-I$(PROTO_DIR)/usr/include
CFLAGS +=	-O2 -Wall -D_XOPEN_SOURCE=500 -D__EXTENSIONS__ $(CPPFLAGS)

LIBS +=	-lsocket -lnsl -llgrp -lkstat -libverbs

COMPONENT_PREP_ACTION = \
	cp rds-vendor.c $(@D)/

CLEANUP_DIRS =	$(PROTOUSRBINDIR)/net

CLEANUP_FILES =\
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man7/rds.7\
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man7rds-rdma.7

COMPONENT_POST_INSTALL_ACTION =\
	$(RM) $(CLEANUP_FILES);\
	$(RM) $(CLEANUP_DIRS)

COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ENV += INSTALL=$(INSTALL)

COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

test:		$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
