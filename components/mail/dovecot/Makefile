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

USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         dovecot
COMPONENT_VERSION=      2.3.19.1
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      DOVECOT - The Secure IMAP server
COMPONENT_DESCRIPTION=	Dovecot is an open source IMAP and POP3 email server for \
		Linux/UNIX-like systems, written with security primarily in mind. \
		Dovecot is an excellent choice for both small and large installations. \
		It's fast, simple to set up, requires no special administration \
		and it uses very little memory.
COMPONENT_PROJECT_URL=  https://dovecot.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_SIG_URL=	$(COMPONENT_PROJECT_URL)/releases/2.3/$(COMPONENT_ARCHIVE).sig
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/releases/2.3/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:db5abcd87d7309659ea6b45b2cb6ee9c5f97486b2b719a5dd05a759e1f6a5c51
COMPONENT_FMRI=         mail/dovecot
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_LICENSE=      MIT,LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV+=		PANDOC=false
CONFIGURE_ENV+=		CPPFLAGS=-I/usr/include/openldap

PATH=$(PATH.gnu):$(MYSQL_BINDIR)

CONFIGURE_OPTIONS+= --sysconfdir=/etc \
		    --localstatedir=/var \
		    --libexecdir=/usr/lib \
                    --with-gssapi=plugin \
                    --with-ldap=plugin \
                    --with-sql=plugin \
                    --with-lua=plugin \
                    --with-ssl=openssl \
		    --with-ioloop=poll \
		    --with-notify=none \
                    --with-sodium \
                    --with-mysql \
                    --with-pgsql \
		    --enable-static=no \
		    --without-systemd \
		    SSL_CFLAGS=-I$(OPENSSL_INCDIR) \
		    SSL_LIBS="-L$(OPENSSL_LIBDIR) -lssl -lcrypto" \
		    LDFLAGS="-lldap_r"

# RPATH needed to make 'make REQUIRED_PACKAGES' happy
COMPONENT_POST_CONFIGURE_ACTION= \
	(cd $(@D) ; $(GSED) -i -e 's:^LDFLAGS = .*:LDFLAGS = $(NOPLUGIN_LDFLAGS) -Wl,-rpath=$(MYSQL_LIBDIR) -Wl,-rpath=$(PG_LIBDIR):' -e 's:mariadb/10.1:mariadb/10.6:g' src/lib-sql/Makefile )

COMPONENT_TEST_ARGS+=   -k
COMPONENT_TEST_TRANSFORMS = \
	'-n ' \
        '-e "/: ok$$/p" ' \
        '-e "/tests failed$$/p" ' \
        '-e "/: FAILED$$/p" '

# manually added dependencies
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += database/mariadb-106
REQUIRED_PACKAGES += database/mariadb-106/client

# Auto-generated dependencies
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += database/mariadb-106/library
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/lz4
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua-53
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/gss
