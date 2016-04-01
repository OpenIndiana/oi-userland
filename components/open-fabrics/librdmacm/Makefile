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

#
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../ofed-component-macros.mk

COMPONENT_NAME=		librdmacm
COMPONENT_VERSION=	1.0.21
COMPONENT_ARCHIVE_HASH=	\
	sha256:bd99d29d24338f0bcc7258f7cde32dc06e5a85139938c2f655c5d5dd4ae6a27b
COMPONENT_ARCHIVE_URL= https://www.openfabrics.org/downloads/rdmacm/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/ofuv_lib

include ../ofed-component.mk

LIBS += -libverbs

CONFIGURE_OPTIONS += --disable-rsocket-utils

CLEANUP_FILES =\
	$(PROTOUSRINCDIR)/infiniband/ib.h\
	$(PROTOUSRINCDIR)/rdma/rdma_cma_abi.h\
	$(PROTOUSRLIBDIR)/$(COMPONENT_NAME).la\
	$(PROTOUSRLIBDIR64)/$(COMPONENT_NAME).la
	
COMPONENT_PREP_ACTION = \
	$(TOUCH) $(COMPONENT_SRC)/Makefile.in

COMPONENT_POST_INSTALL_ACTION = \
	$(RM) $(CLEANUP_FILES);

