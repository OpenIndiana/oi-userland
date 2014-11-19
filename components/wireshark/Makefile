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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		wireshark
COMPONENT_VERSION=	1.10.11
COMPONENT_PROJECT_URL=	http://www.wireshark.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:8aaf07584c023c02f7db6aed5226a259c7da0da660f356efd3088ce936dd5034
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/src/all-versions/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/wireshark

TPNO=			20429

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# Micro version for easy libraries packaging
MICRO_VERSION:= $(shell echo $(COMPONENT_VERSION) | awk -F. '{ print $$3 }')
PKG_MACROS+= MICRO_VERSION=$(MICRO_VERSION)

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

PATCH_LEVEL=0

# We don't have automake 1.14 yet. Thus need to reconfigure with older one.
COMPONENT_PREP_ACTION += ( cd $(@D) ; $(CONFIG_SHELL) autogen.sh );

CONFIGURE_OPTIONS +=	--bindir=/usr/sbin
CONFIGURE_OPTIONS +=	--disable-usr-local
CONFIGURE_OPTIONS +=	--disable-randpkt
CONFIGURE_OPTIONS +=	--disable-dftest
CONFIGURE_OPTIONS +=	--with-krb5
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)" 
CONFIGURE_OPTIONS +=	PATH="/usr/perl5/bin:/usr/gnu/bin:$(PATH)"

# Use the 64-bit versions of pkg-config files
CONFIGURE_ENV +=	PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"

# Version 1.10 (libwireshark.so) doesn't play nicely with -Bdirect.
LD_B_DIRECT=

# We need to avoid RPATH=/usr/lib in Wireshark libraries so that we can
# create successfully IPS package of different Wireshark branch than is
# installed on build system without dependency errors.
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D); \
	sed -e 's,-R/usr/lib/$(MACH64),,' \
	    -e 's,-R/usr/lib,,' \
	    -e 's,-R\$$libdir,,' \
		config.status > config.status.new; \
	mv config.status.new config.status; \
	chmod 755 config.status; \
	./config.status)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
