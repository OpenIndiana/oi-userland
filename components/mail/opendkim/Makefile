#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022 Friedrich Kink
#

USE_OPENSSL11=		yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         opendkim
COMPONENT_VERSION=      2.10.3
COMPONENT_REVISION =	1
COMPONENT_SUMMARY=      OpenDKIM is an open source implementation of the DKIM (Domain Keys Identified Mail) sender authentication system
COMPONENT_DESCRIPTION=	OpenDKIM is an open source implementation of the DKIM \
			(Domain Keys Identified Mail) sender authentication system proposed \
			by the E-mail Signing Technology Group (ESTG), now standardized by \
			the IETF (RFC6376). It also includes implementations of the RFC5617) \
			Vouch By Reference (VBR, RFC5518) proposed standard and the experimental \
			Authorized Third Party Signatures protocol (ATPS, RFC6541).
COMPONENT_PROJECT_URL=  http://opendkim.org/
COMPONENT_FMRI=         mail/opendkim
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  https://sourceforge.net/projects/opendkim/files/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:43a0ba57bf942095fe159d0748d8933c6b1dd1117caf0273fa9a0003215e681b
COMPONENT_LICENSE=      Copyright (c) 2009, 2010, 2012, 2013, The Trusted Domain Project.
COMPONENT_LICENSE_FILE= LICENSE

USE_DEFAULT_TEST_TRANSFORMS = yes

include $(WS_MAKE_RULES)/common.mk

PATH=			$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION= ( cd $(SOURCE_DIR) && autoreconf --install )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc/mail \
			--enable-diffheaders \
			--enable-identity_header \
			--enable-rbl \
			--enable-rate_limit \
			--enable-replace_rules \
			--enable-atps \
			--enable-vbr \
			--enable-reprrd \
			--enable-statsext \
			--enable-stats \
			--enable-sender_macro \
			--with-openldap \
			--with-openssl=$(OPENSSL_PREFIX) \
			--with-lmdb \
			--with-sasl \
			--with-erlang \
			--with-odbx \
			--with-libcurl \
			--with-milter \
			--with-tre \
			--with-libjansson \
			--with-db \
			--enable-sender_macro \
			--with-libmemcached \
			--with-lua \
			"LIBS=-lnsl -lldap_r -lldap -llber" \
			"LIBLUA_LIBS=" \
			"LIBMILTER_LIBDIRS=" \
			"LDFLAGS=-L$(OPENSSL_PREFIX)/lib/amd64 -lssl -lcrypto" \
			"CPPFLAGS=-I/usr/include/openldap -I$(SOURCE_DIR)/libut"

unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS += "-e '/XFAIL: /p'"
COMPONENT_TEST_TRANSFORMS += "-e '/XPASS: /p'"
COMPONENT_TEST_TRANSFORMS += "-e '/^=======/p'"

REQUIRED_PACKAGES += runtime/erlang

# Auto-generated dependencies
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += database/lmdb
REQUIRED_PACKAGES += image/rrdtool
REQUIRED_PACKAGES += library/jansson
REQUIRED_PACKAGES += library/libmemcached
REQUIRED_PACKAGES += library/libmilter
REQUIRED_PACKAGES += library/opendbx
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/tre
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
