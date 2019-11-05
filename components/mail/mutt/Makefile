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

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mutt
COMPONENT_VERSION=	1.12.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:bc42750ce8237742b9382f2148fc547a8d8601aa4a7cd28c55fe7ca045196882
COMPONENT_ARCHIVE_URL=	ftp://ftp.mutt.org/pub/mutt/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.mutt.org/
COMPONENT_FMRI=		mail/mutt
COMPONENT_LICENSE_FILE=	mutt.license
COMPONENT_LICENSE=	GPLv2

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CFLAGS +=			-I$(USRINCDIR)/idn2

CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=		--sysconfdir="$(ETCDIR)/$(COMPONENT_NAME)"
CONFIGURE_OPTIONS  +=		--enable-pop
CONFIGURE_OPTIONS  +=		--enable-imap
CONFIGURE_OPTIONS  +=		--enable-smtp
CONFIGURE_OPTIONS  +=		--enable-hcache
CONFIGURE_OPTIONS  +=		--enable-sidebar
CONFIGURE_OPTIONS  +=		--enable-debug
CONFIGURE_OPTIONS  +=		--with-gdbm
CONFIGURE_OPTIONS  +=		--with-regex
CONFIGURE_OPTIONS  +=		--with-slang
CONFIGURE_OPTIONS  +=		--with-ssl
CONFIGURE_OPTIONS  +=		--with-idn2
CONFIGURE_OPTIONS  +=		--with-wc-funcs
CONFIGURE_OPTIONS  +=		--with-sasl

REQUIRED_PACKAGES += runtime/perl-522
# Auto-generated dependencies
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/libidn2
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/slang
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libsasl
