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

COMPONENT_NAME=		opensm
COMPONENT_VERSION=	3.3.19
COMPONENT_ARCHIVE_HASH=	\
    sha256:2ff7729d5566e6569a387603aa188580dede20c929c0f22baf8eb6d36d8925b6
COMPONENT_ARCHIVE_URL=	https://www.openfabrics.org/downloads/management/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/ofuv_lib
COMPONENT_ANITYA_ID=	2563

include ../ofed-component.mk

CFLAGS += -std=gnu99

LIBS +=	-libverbs -libumad -libmad

CLEANUP_FILES = \
	$(PROTOUSRLIBDIR)/libosmcomp.la \
	$(PROTOUSRLIBDIR64)/libosmcomp.la \
	$(PROTOUSRLIBDIR)/libosmvendor.la \
	$(PROTOUSRLIBDIR64)/libosmvendor.la \
	$(PROTOUSRLIBDIR)/libopensm.la \
	$(PROTOUSRLIBDIR64)/libopensm.la \
	$(PROTOUSRSBINDIR)/opensm \
	$(PROTOUSRSBINDIR)/osmtest \
	$(PROTOETCDIR)/init.d/opensmd \
	$(PROTOUSRSHAREMAN8DIR)/opensm.8 \
	$(PROTOUSRSHAREMAN8DIR)/osmtest.8

COMPONENT_POST_INSTALL_ACTION = \
	$(RM) $(CLEANUP_FILES);\
	$(RM) $(PROTOUSRLIBDIR)/$(COMPONENT_NAME).la;\
	$(RM) $(PROTOUSRLIBDIR64)/$(COMPONENT_NAME).la;\
	$(RM) -r $(PROTOETCDIR)

COMPONENT_PRE_BUILD_ACTION =\
	$(MV) $(PROTOUSRLIBDIR)/libibverbs.la\
		$(PROTOUSRLIBDIR)/.libibverbs.la;\
	$(MV) $(PROTOUSRLIBDIR64)/libibverbs.la\
		$(PROTOUSRLIBDIR64)/.libibverbs.la

COMPONENT_POST_BUILD_ACTION =\
	$(MV) $(PROTOUSRLIBDIR)/.libibverbs.la\
		$(PROTOUSRLIBDIR)/libibverbs.la;\
	$(MV) $(PROTOUSRLIBDIR64)/.libibverbs.la\
		$(PROTOUSRLIBDIR64)/libibverbs.la

