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

COMPONENT_NAME=		libibumad
COMPONENT_VERSION=	1.3.7
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:4999cb9ff5c7243027d8a154d6b27d1efffaa4359b84447731c5ef545fb72229
COMPONENT_ARCHIVE_URL=	http://www.openfabrics.org/downloads/management/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include ../ofed.mk

LIBS +=	-lsocket -lnsl -libverbs

CLEANUP_FILES = $(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_free.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_done.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_send.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_recv.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_init.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_dump.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_poll.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_size.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_debug.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_alloc.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_get_ca.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_get_fd.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_status.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_get_mad.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_set_grh.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_set_addr.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_get_pkey.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_get_port.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_set_pkey.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_register.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_addr_dump.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_open_port.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_release_ca.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_close_port.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_unregister.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_set_grh_net.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_get_mad_addr.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_set_addr_net.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_release_port.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_register_oui.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_get_cas_names.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_get_issm_path.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/umad_get_ca_portguids.3

COMPONENT_POST_INSTALL_ACTION = \
	$(RM) $(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)/$(COMPONENT_NAME).la;\
	$(RM) $(PROTO_DIR)/$(CONFIGURE_LIBDIR.64)/$(COMPONENT_NAME).la;\
	$(RM) $(CLEANUP_FILES)


# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

test:		$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
