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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		screen
COMPONENT_VERSION=	4.4.0
COMPONENT_ARCHIVE_HASH=	\
    sha256:ef722a54759a3bf23aad272bbf33c414c1078cad6bcd982fada93c0d7917218b

TPNO=			29565	

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/gnu-component.mk

# Fix 64-bit linking via compiler.
LDFLAGS += $(CC_BITS)

CONFIGURE_OPTIONS +=	--enable-colors256
CONFIGURE_OPTIONS +=	--with-sys-screenrc=$(ETCDIR)/screenrc
CONFIGURE_OPTIONS +=	--disable-socket-dir
CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)

PROTOTERMINFODIR=$(PROTOUSRSHARELIBDIR)/terminfo

$(PROTOTERMINFODIR):
	$(MKDIR) $@

$(INSTALL_64):	$(PROTOTERMINFODIR)
