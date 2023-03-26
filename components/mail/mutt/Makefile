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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright 2019, Michal Nowak
#
# Only openssl-1.0 is supported by mutt (for newer openssl version some symbols cannot be found):
USE_OPENSSL10= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mutt
COMPONENT_VERSION=	2.2.10
COMPONENT_SUMMARY=	Mutt is a small but very powerful text-based mail client for Unix operating systems.
COMPONENT_PROJECT_URL=	http://www.mutt.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:4d773f22422f79096f7b94b57bee45654ad9a25165dbb36463c58295b4cd3d88
COMPONENT_ARCHIVE_URL=	http://ftp.mutt.org/pub/mutt/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		mail/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYRIGHT

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CFLAGS += -I$(USRINCDIR)/idn2

CONFIGURE_OPTIONS += LDFLAGS=-L$(OPENSSL_PREFIX)/lib/$(MACH64)
CONFIGURE_OPTIONS += CPPFLAGS=-I$(OPENSSL_PREFIX)/include
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += --sysconfdir="$(ETCDIR)/$(COMPONENT_NAME)"
CONFIGURE_OPTIONS += --enable-pop
CONFIGURE_OPTIONS += --enable-imap
CONFIGURE_OPTIONS += --enable-smtp
CONFIGURE_OPTIONS += --enable-hcache
CONFIGURE_OPTIONS += --enable-sidebar
CONFIGURE_OPTIONS += --enable-debug
CONFIGURE_OPTIONS += --with-gdbm
CONFIGURE_OPTIONS += --with-regex
CONFIGURE_OPTIONS += --with-slang
CONFIGURE_OPTIONS += --with-ssl=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS += --with-idn2
CONFIGURE_OPTIONS += --with-wc-funcs
CONFIGURE_OPTIONS += --with-sasl

# Auto-generated dependencies
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/libidn2
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/slang
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libsasl
