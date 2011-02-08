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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		tar
COMPONENT_VERSION=	1.25
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha1:0f0c090e51d127cbeffbb9aeeb90db1181d82aed
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/tar/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# workaround for CR 6998994
sparc_COPTFLAG = -xO2

CONFIGURE_OPTIONS +=	--with-rmt=/usr/sbin/rmt
CONFIGURE_OPTIONS +=	--libexecdir=/usr/sbin
CONFIGURE_OPTIONS +=	--program-prefix=g
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)" 

GNUPROGS =	tar
GNUMAN1 =	tar.1
SFWPROGS =	gtar

PROTOGNULINKS = $(GNUPROGS:%=$(PROTOGNUBIN)/%)

$(PROTOGNULINKS):	$(PROTOGNUBIN)
	$(RM) $@ ; $(SYMLINK) ../../bin/g$(@F) $@

PROTOGNUMAN1LINKS = $(GNUMAN1:%=$(PROTOGNUSHAREMAN1)/%)

$(PROTOGNUMAN1LINKS):	$(PROTOGNUSHAREMAN1)
	$(RM) $@ ; $(SYMLINK) ../../../../share/man/man1/g$(@F) $@

include ../../make-rules/shared-targets.mk

COMPONENT_BUILD_TARGETS = all

build:		$(BUILD_32)

install: $(PROTOUSRSHAREMAN1DIR) $(INSTALL_32) \
    $(PROTOGNULINKS) $(PROTOGNUMAN1LINKS) $(PROTOSFWLINKS)
	$(CP) -f $(COMPONENT_DIR)/gtar.1.sunman $(PROTOUSRSHAREMAN1DIR)/gtar.1

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
