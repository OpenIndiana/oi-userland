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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../ofed-component-macros.mk

COMPONENT_NAME=		perftest
COMPONENT_VERSION=	1.3.0
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-0.42.gf350d3d.tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:164d32753ab87ba3152c84f69bf16bb592d77b922e66e753bd9ad0e229675793
COMPONENT_BUGDB=	utility/ofuv_tools

INSTALL_TARGET=
include ../ofed-component.mk

MAN1FILES =	ib_write_bw.1 \
		ib_read_bw.1 \
		ib_send_bw.1 \
		rdma_bw.1

MAN8FILES = ib_clock_test.8

include $(WS_MAKE_RULES)/shared-targets.mk

LIBS += -lkstat -lrdmacm -libverbs -libumad -libmad

LDFLAGS +=	-L$(PROTO_DIR)/$(CONFIGURE_LIBDIR.$(BITS))
CFLAGS +=	$(SHARED_INCLUDES) -fgnu89-inline

COMMON_ARGS  +=	CC="$(CC)"
COMMON_ARGS  +=	CFLAGS="$(CFLAGS)"
COMMON_ARGS  +=	LDFLAGS="$(LDFLAGS) $(LIBS)"
COMMON_ARGS  +=	INSTALL=$(INSTALL)
COMMON_ARGS  += BINDIR=$(CONFIGURE_BINDIR.$(BITS))
COMPONENT_BUILD_ARGS  +=	$(COMMON_ARGS)
COMPONENT_INSTALL_ARGS  +=	$(COMMON_ARGS)

# need to translate ctrl-M in downloaded send_bw.c
COMPONENT_POST_UNPACK_ACTION= \
		cd $(@D); \
		/usr/bin/tr -d '\r' < send_bw.c > send_bw.c.tmp; \
		mv send_bw.c.tmp send_bw.c; \
		cd ..;

COMPONENT_PREP_ACTION = $(TOUCH) $(@D)/configure

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

# common targets
install:	$(INSTALL_64) $(PROTOMAN1FILES)	$(PROTOMAN8FILES)

