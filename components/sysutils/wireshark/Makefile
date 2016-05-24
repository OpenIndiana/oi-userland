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
# Copyright (c) 2011, 2014, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		wireshark
COMPONENT_VERSION=	2.0.2
COMPONENT_PROJECT_URL=	http://www.wireshark.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:e921fb072085a5654d899949bb561d0687f4819f7b63ba35777bb949a9b6b9c1
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/src/all-versions/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/wireshark

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Micro version for easy libraries packaging
MICRO_VERSION:= $(shell echo $(COMPONENT_VERSION) | awk -F. '{ print $$3 }')
PKG_MACROS+= MICRO_VERSION=$(MICRO_VERSION)

PATCH_LEVEL=0

# We don't have automake 1.14 yet. Thus need to reconfigure with older one.
COMPONENT_PREP_ACTION += ( cd $(@D) ; $(CONFIG_SHELL) autogen.sh );

CONFIGURE_BINDIR.$(BITS) = $(CONFIGURE_SBINDIR.$(BITS))

CONFIGURE_OPTIONS +=	--disable-usr-local
CONFIGURE_OPTIONS +=	--disable-androiddump
CONFIGURE_OPTIONS +=	--disable-randpkt
CONFIGURE_OPTIONS +=	--disable-dftest
CONFIGURE_OPTIONS +=	--with-krb5
CONFIGURE_OPTIONS +=	--with-qt=no
CONFIGURE_OPTIONS +=	--with-gtk2=yes
CONFIGURE_OPTIONS +=	PATH="/usr/perl5/bin:/usr/gnu/bin:$(PATH)"

LDFLAGS += -lsocket -lnsl
LD_B_DIRECT=

# We need to avoid RPATH=/usr/lib in Wireshark libraries so that we can
# create successfully IPS package of different Wireshark branch than is
# installed on build system without dependency errors.
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D); \
	sed -e 's,-L/usr/lib -R/usr/lib,,' -e 's,-R/usr/lib,,' \
		config.status > config.status.new; \
	mv config.status.new config.status; \
	chmod 755 config.status; \
	./config.status)

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
