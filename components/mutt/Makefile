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

COMPONENT_NAME=		mutt
COMPONENT_VERSION=	1.5.21
COMPONENT_ARCHIVE_HASH=	\
    sha256:2141f36e8d0f4f71c9ca6780001e7cc679fe313e643953fc07f001223e67c4a0
COMPONENT_ARCHIVE_URL=	ftp://ftp.mutt.org/mutt/devel/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.mutt.org/

TPNO=			9259

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS  +=		--sysconfdir="$(ETCDIR)/$(COMPONENT_NAME)"
CONFIGURE_OPTIONS  +=		--enable-pop
CONFIGURE_OPTIONS  +=		--enable-imap
CONFIGURE_OPTIONS  +=		--enable-smtp
CONFIGURE_OPTIONS  +=		--enable-hcache
CONFIGURE_OPTIONS  +=		--with-gdbm
CONFIGURE_OPTIONS  +=		--with-regex
CONFIGURE_OPTIONS  +=		--with-slang
CONFIGURE_OPTIONS  +=		--with-ssl
CONFIGURE_OPTIONS  +=		--with-idn
CFLAGS +=			-I"$(USRINCDIR)/idn"
CONFIGURE_OPTIONS  +=		--with-wc-funcs
CONFIGURE_OPTIONS  +=		--with-sasl

# Add in the C compiler information to the muttbug (a.k.a. flea) script.
COMPONENT_POST_CONFIGURE_ACTION = \
	$(GSED) -i 's%XXX-CUSAGE-XXX%$(shell $(CC) -V 2>&1 | head -1)%' \
	$(BUILD_DIR_64)/muttbug.sh 

REQUIRED_PACKAGES += data/docbook/docbook-dtds
REQUIRED_PACKAGES += data/docbook/docbook-style-dsssl
REQUIRED_PACKAGES += data/docbook/docbook-style-xsl
REQUIRED_PACKAGES += data/xml-common
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/libidn
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/slang
REQUIRED_PACKAGES += runtime/perl-512
REQUIRED_PACKAGES += runtime/perl-520
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libsasl
REQUIRED_PACKAGES += system/library/security/libsasl2
