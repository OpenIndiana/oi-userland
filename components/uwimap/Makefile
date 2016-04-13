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
# Copyright 2011 EveryCity Ltd. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		imap
COMPONENT_VERSION=	2007e
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:4b1137b87249782496ec3eeacaf83bbf09312a7d2ae3aead262179041b55565f
COMPONENT_ARCHIVE_URL=	ftp://ftp.cac.washington.edu/imap/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

IPS_COMPONENT_VERSION=	0.2007.5

COMPONENT_BUILD_TARGETS+=	ec IP=6 SHLIBBASE=c-client SHLIBNAME=libc-client.so.1 EXTRACFLAGS="$(CFLAGS)" EXTRALDFLAGS="$(LDFLAGS)"

PATH=	/usr/gnu/bin:/usr/bin:$PATH

echoenv:	
		env

build:		echoenv $(BUILD_32_and_64)

install:        build
	$(MKDIR) -p $(PROTO_DIR)/usr/lib/$(MACH64)
	$(MKDIR) -p $(PROTO_DIR)/usr/include/c-client
	$(CP) $(BUILD_DIR_32)/c-client/libc-client.so.1 $(PROTO_DIR)/usr/lib/
	$(CP) $(BUILD_DIR_64)/c-client/libc-client.so.1 $(PROTO_DIR)/usr/lib/$(MACH64)
	$(CP) $(SOURCE_DIR)/src/osdep/unix/*.h $(PROTO_DIR)/usr/include/c-client/
	$(CP) $(SOURCE_DIR)/src/c-client/*.h $(PROTO_DIR)/usr/include/c-client/
	$(CP) $(BUILD_DIR_32)/c-client/linkage.h $(PROTO_DIR)/usr/include/c-client/

