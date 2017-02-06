
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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../ofed-component-macros.mk

COMPONENT_NAME=		libibverbs
COMPONENT_VERSION=	1.1.8
COMPONENT_ARCHIVE_HASH=	\
	sha256:7c766e679e1e6dbcb37bdfc624c64310787e3a380baf7ee1eebde39c6991828f
COMPONENT_ARCHIVE_URL= https://www.openfabrics.org/downloads/verbs/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/ofuv_lib

INSTALL_TARGET=
include ../ofed-component.mk

MAN3FILES =	ibv_alloc_shpd.3 \
		ibv_reg_mr_relaxed.3 \
		ibv_share_pd.3 \
		ibv_gid_reachable.3 \
		ibv_register_sm_events.3

include $(WS_MAKE_RULES)/shared-targets.mk
include $(WS_MAKE_RULES)/lint-libraries.mk

# add flags to get at extra bits from other components' source trees
CPPFLAGS +=	-I$(PWD)/../libmlx4/libmlx4-1.0.6/src
CPPFLAGS +=	-I$(PWD)/../librdmacm/librdmacm-1.0.21/include

LIBS +=	-lkstat

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)/infiniband

# --disable-libcheck is not a supported option for this component
DISABLE_LIBCHECK=

COMPONENT_PREP_ACTION = \
	cp ofa_solaris.h $(@D)/include/infiniband ; \
	cp solaris_compatibility.c $(@D)/src ; \
	cd ../libmlx4; gmake prep; \
	cd ../librdmacm; gmake prep

# Userland lint-install code (lint-libraries.mk) would install llib-libverbs.ln
# to the directory 'build/prototype/$(MACH)/usr/lib/$(MACH64)',
# which doesn't exist and must be created manually to let the installation pass.
COMPONENT_PRE_INSTALL_ACTION = \
        $(MKDIR) $(BUILD_DIR)/prototype/$(MACH)/usr/lib/$(MACH64)

COMPONENT_POST_INSTALL_ACTION = \
	$(RM) $(PROTO_DIR)/$(CONFIGURE_BINDIR.$(BITS))/ibv_uc_pingpong; \
	$(RM) $(PROTOUSRSHAREMAN1DIR)/ibv_uc_pingpong.1 \
	$(PROTOUSRSHAREMAN3DIR)/ibv_reg_xrc_rcv_qp.3 \
	$(PROTOUSRSHAREMAN3DIR)/ibv_create_xrc_srq.3 \
	$(PROTOUSRSHAREMAN3DIR)/ibv_open_xrc_domain.3 \
	$(PROTOUSRSHAREMAN3DIR)/ibv_close_xrc_domain.3 \
	$(PROTOUSRSHAREMAN3DIR)/ibv_unreg_xrc_rcv_qp.3 \
	$(PROTOUSRSHAREMAN3DIR)/ibv_query_xrc_rcv_qp.3 \
	$(PROTOUSRSHAREMAN3DIR)/ibv_create_xrc_rcv_qp.3 \
	$(PROTOUSRSHAREMAN3DIR)/ibv_modify_xrc_rcv_qp.3; \
	$(INSTALL) -c llib-libverbs $(PROTOUSRLIBDIR)/llib-libverbs

install:	$(INSTALL_64) $(PROTOMAN3FILES)

