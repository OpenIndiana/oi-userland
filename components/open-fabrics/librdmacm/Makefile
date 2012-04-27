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

COMPONENT_NAME=		librdmacm
COMPONENT_VERSION=	1.0.14.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:b74d367415b4f294f3821955428f3e362b91f779042c88970f99941216c13a7c
COMPONENT_ARCHIVE_URL=	http://www.openfabrics.org/downloads/rdmacm/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include ../ofed.mk

LIBS += -libverbs -lsocket -lnsl

CLEANUP_FILES =\
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man1/rdma_server.1\
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man1/rdma_client.1\
	$(PROTO_DIR)/$(CONFIGURE_MANDIR)/man3/rdma_set_option.3\
	$(PROTOUSRBINDIR)/rdma_server\
	$(PROTOUSRBINDIR)/rdma_client\
	$(PROTOUSRBINDIR)/$(MACH64)/rdma_server\
	$(PROTOUSRBINDIR)/$(MACH64)/rdma_client\
	$(PROTOUSRBINDIR)/$(MACH64)/mckey\
	$(PROTOUSRBINDIR)/$(MACH64)/rping\
	$(PROTOUSRBINDIR)/$(MACH64)/udaddy\
	$(PROTOUSRBINDIR)/$(MACH64)/ucmatose\
	$(PROTOUSRINCDIR)/infiniband/ib.h\
	$(PROTOUSRINCDIR)/rdma/rdma_cma_abi.h\
	$(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)/$(COMPONENT_NAME).la\
	$(PROTO_DIR)/$(CONFIGURE_LIBDIR.64)/$(COMPONENT_NAME).la
	
COMPONENT_PREP_ACTION = \
	$(TOUCH) $(COMPONENT_SRC)/Makefile.in

COMPONENT_POST_INSTALL_ACTION = \
	$(RM) $(CLEANUP_FILES);

#COMPONENT_PRE_CONFIGURE_ACTION

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

test:		$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
