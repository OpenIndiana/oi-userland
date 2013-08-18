#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2013 Louis M. Picciano. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME			= sqlite-3
COMPONENT_VERSION		= 3.7.17
COMPONENT_SRC			= sqlite-autoconf-3071700
COMPONENT_ARCHIVE		= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH	= \
	sha256:8ff46d0baa9e64c0815544e829e985f1161c096aa6344c8f430791dbeadc2baf
COMPONENT_ARCHIVE_URL=	http://www.sqlite.org/2013/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CFLAGS				+= "$(CC_BITS)"

CONFIGURE_OPTIONS	+= CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS	+=	--sysconfdir=$(ETCDIR)

include ../../make-rules/shared-targets.mk

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
