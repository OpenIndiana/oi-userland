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

COMPONENT_NAME=		libibverbs
COMPONENT_VERSION=	1.1.4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-1.22.g7257cd3.tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1e04aa9d518e3dc372fdda6bd25bf072caae4c85c38d0ae095a614104aa583d4
COMPONENT_ARCHIVE_URL=	http://www.openfabrics.org/downloads/libibverbs/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include ../ofed.mk

# add flags to get at extra bits from other components' source trees
CPPFLAGS +=	-I$(PWD)/../libmlx4/libmlx4-1.0.1/src
CPPFLAGS +=	-I$(PWD)/../librdmacm/librdmacm-1.0.14.1/include

LIBS +=	-lsocket -lnsl -lkstat

# --disable-libcheck is not a supported option for this component
DISABLE_LIBCHECK=

COMPONENT_PREP_ACTION = \
	cp ofa_solaris.h $(@D)/include/infiniband ; \
	cp solaris_compatibility.c $(@D)/src ; \
	cd ../libmlx4; gmake prep; \
	cd ../librdmacm; gmake prep

COMPONENT_POST_INSTALL_ACTION = \
	$(RM) $(PROTO_DIR)/$(CONFIGURE_BINDIR.$(BITS))/ibv_uc_pingpong; \
	$(RM) $(PROTO_DIR)/$(CONFIGURE_BINDIR.64)/ibv_devices \
	$(PROTO_DIR)/$(CONFIGURE_BINDIR.64)/ibv_devinfo \
	$(PROTO_DIR)/$(CONFIGURE_BINDIR.64)/ibv_asyncwatch \
	$(PROTO_DIR)/$(CONFIGURE_BINDIR.64)/ibv_rc_pingpong \
	$(PROTO_DIR)/$(CONFIGURE_BINDIR.64)/ibv_uc_pingpong \
	$(PROTO_DIR)/$(CONFIGURE_BINDIR.64)/ibv_ud_pingpong \
	$(PROTO_DIR)/$(CONFIGURE_BINDIR.64)/ibv_srq_pingpong \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man1/ibv_uc_pingpong.1 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/ibv_reg_xrc_rcv_qp.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/ibv_create_xrc_srq.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/ibv_open_xrc_domain.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/ibv_close_xrc_domain.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/ibv_unreg_xrc_rcv_qp.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/ibv_query_xrc_rcv_qp.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/ibv_create_xrc_rcv_qp.3 \
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/ibv_modify_xrc_rcv_qp.3
	
# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

test:		$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
