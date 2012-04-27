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

COMPONENT_NAME=		opensm
COMPONENT_VERSION=	3.3.9
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:b8f333815e9d145cbb29310a38d2f2e39f9727b30eb6b15cb0d81fb9db39a2e1
COMPONENT_ARCHIVE_URL=	http://www.openfabrics.org/downloads/management/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include ../ofed.mk

CFLAGS += -std=gnu99
LIBS +=	-libverbs -lsocket -lnsl -libumad -libmad

CONFIGURE_ENV	+=	CPPFLAGS="$(CPPFLAGS)"

CLEANUP_FILES = \
	$(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)/libosmcomp.la \
	$(PROTO_DIR)/$(CONFIGURE_LIBDIR.64)/libosmcomp.la \
        $(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)/libosmvendor.la \
	$(PROTO_DIR)/$(CONFIGURE_LIBDIR.64)/libosmvendor.la \
        $(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)/libopensm.la \
	$(PROTO_DIR)/$(CONFIGURE_LIBDIR.64)/libopensm.la \
	$(PROTOUSRSBINDIR)/opensm \
	$(PROTOUSRSBINDIR)/osmtest \
        $(PROTO_DIR)/usr/etc/init.d/opensmd \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man8/opensm.8 \
        $(PROTO_DIR)/$(CONFIGURE_MANDIR)/man8/osmtest.8

COMPONENT_POST_INSTALL_ACTION = \
	$(RM) $(CLEANUP_FILES);\
	$(RM) $(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)/$(COMPONENT_NAME).la;\
	$(RM) $(PROTO_DIR)/$(CONFIGURE_LIBDIR.64)/$(COMPONENT_NAME).la;\
	$(RM) -r $(PROTO_DIR)/usr/etc

COMPONENT_PRE_BUILD_ACTION =\
	$(MV) $(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)/libibverbs.la\
	$(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)/.libibverbs.la;\
	$(MV) $(PROTO_DIR)/$(CONFIGURE_LIBDIR.64)/libibverbs.la\
	$(PROTO_DIR)/$(CONFIGURE_LIBDIR.64)/.libibverbs.la

COMPONENT_POST_BUILD_ACTION =\
	$(MV) $(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)/.libibverbs.la\
	$(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)/libibverbs.la;\
	$(MV) $(PROTO_DIR)/$(CONFIGURE_LIBDIR.64)/.libibverbs.la\
	$(PROTO_DIR)/$(CONFIGURE_LIBDIR.64)/libibverbs.la

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

test:		$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
