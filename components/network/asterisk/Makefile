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
# Copyright 2016 Andrey Sokolov. All rights reserved.
# Copyright 2017 Alexander Pyhalov
# Copyright 2021 Olaf Bohlen
# Copyright 2023 Friedrich Kink
#

USE_OPENSSL11= yes
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		asterisk
COMPONENT_VERSION=	20.3.0
COMPONENT_SUMMARY=	Asterisk is an all-purpose telephony server
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:2e70b4bb40114966c6572eae38b5106b588a7a759d41f1c90a6032407dd60463
COMPONENT_PROJECT_URL=	https://www.asterisk.org
COMPONENT_ARCHIVE_URL=	https://downloads.asterisk.org/pub/telephony/asterisk/old-releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		network/asterisk
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS) 
include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

PATCH_LEVEL = 0

COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D));

#
# res_geolocation does not build with the illumos linker due to missing capabilities/options
# no workaround known so far
# also remove deprecated functions
#
COMPONENT_POST_CONFIGURE_ACTION += ( \
	cd $(@D); \
	$(GSED) -i -e 's:LDAP_INCLUDE=:LDAP_INCLUDE=-I/usr/include/openldap:' makeopts; \
	$(GSED) -i -e 's/ -lldap-2.6//' makeopts; \
	$(GSED) -i -e 's/LDAP_LIB= -lldap/LDAP_LIB= -lldap-2.6/' makeopts; \
	$(GSED) -i -e "s:-L$(OPENSSL_PREFIX)/lib :-L$(OPENSSL_LIBDIR.$(BITS)) :" makeopts; \
	$(GSED) -i -e "s:$(MYSQL_HOME)$(MYSQL_HOME):$(MYSQL_HOME):g" makeopts; \
	$(GSED) -i -e "s:-L$(MYSQL_LIBDIR):-L$(MYSQL_LIBDIR) -R$(MYSQL_LIBDIR):" makeopts; \
	$(GSED) -i -e "s:-L$(PG_LIBDIR.$(BITS)):-L$(PG_LIBDIR.$(BITS)) -R$(PG_LIBDIR.$(BITS)):" makeopts; \
	$(GMAKE) menuselect.makeopts; \
	./menuselect/menuselect --disable res_geolocation menuselect.makeopts; \
	./menuselect/menuselect --enable format_mp3 menuselect.makeopts; \
	./menuselect/menuselect --enable res_config_mysql menuselect.makeopts; \
	./menuselect/menuselect --enable res_mwi_external menuselect.makeopts; \
	./menuselect/menuselect --enable res_chan_stats menuselect.makeopts; \
	./menuselect/menuselect --enable res_endpoint_stats menuselect.makeopts; \
	./menuselect/menuselect --enable res_stasis_mailbox menuselect.makeopts; \
	./menuselect/menuselect --enable res_mwi_external_ami menuselect.makeopts; \
	./menuselect/menuselect --enable app_voicemail_odbc menuselect.makeopts; \
	./menuselect/menuselect --enable app_saycounted menuselect.makeopts; \
	./menuselect/menuselect --enable app_statsd menuselect.makeopts; \
	./menuselect/menuselect --enable G711_NEW_ALGORITHM menuselect.makeopts; \
	./menuselect/menuselect --enable G711_REDUCED_BRANCHING menuselect.makeopts; \
	./menuselect/menuselect --disable app_adsiprog menuselect.makeopts; \
	./menuselect/menuselect --disable app_getcpeid menuselect.makeopts; \
	./menuselect/menuselect --disable res_adsi menuselect.makeopts; \
	);

CONFIGURE_BINDIR=	/usr/bin
CONFIGURE_SBINDIR=	/usr/sbin

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--localstatedir=/var
CONFIGURE_OPTIONS +=    --with-gnu-ld=no
CONFIGURE_OPTIONS +=	--with-crypto=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS +=	--with-ssl=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS +=	--with-pjproject-bundled
CONFIGURE_OPTIONS +=	--with-gsm=internal
CONFIGURE_OPTIONS +=	--with-ilbc=internal
CONFIGURE_OPTIONS +=	--with-unixodbc
CONFIGURE_OPTIONS +=	--with-ldap
CONFIGURE_OPTIONS +=	--with-gmime
CONFIGURE_OPTIONS +=	--with-netsnmp
CONFIGURE_OPTIONS +=	--with-vorbis
CONFIGURE_OPTIONS +=	--with-ogg
CONFIGURE_OPTIONS +=	--with-opus
CONFIGURE_OPTIONS +=	--with-sdl
CONFIGURE_OPTIONS +=	--with-neon
CONFIGURE_OPTIONS +=	--with-lua
CONFIGURE_OPTIONS +=	--with-tds
CONFIGURE_OPTIONS +=	--with-jansson
CONFIGURE_OPTIONS +=	--with-libedit
CONFIGURE_OPTIONS +=	--with-libxml2
CONFIGURE_OPTIONS +=	--with-libxslt
CONFIGURE_OPTIONS +=	--with-libcurl
CONFIGURE_OPTIONS +=	--with-gtk2
CONFIGURE_OPTIONS +=	--with-popt
CONFIGURE_OPTIONS +=	--with-spandsp
CONFIGURE_OPTIONS +=	--with-speex
CONFIGURE_OPTIONS +=	--with-speexdsp
CONFIGURE_OPTIONS +=	--with-mysqlclient=$(MYSQL_HOME)
#CONFIGURE_OPTIONS +=	--with-avcodec
CONFIGURE_OPTIONS +=	--with-postgres=$(PG_HOME)
CONFIGURE_OPTIONS +=	NOISY_BUILD=yes
CONFIGURE_OPTIONS +=	PKG_CONFIG_PATH=/usr/lib/$(MACH64)/pkgconfig
CONFIGURE_OPTIONS +=	LDFLAGS="-m64 -lldap-2.6 -L$(JPEG_LIBDIR)"
CONFIGURE_OPTIONS +=	CPPFLAGS="-I/usr/include/jansson -I/usr/include/odbc -I/usr/include/openldap"
# HAVE_OPENSSL_BIO_METHOD not properly recognised by configure therefore expiclitly set
CONFIGURE_OPTIONS +=	CFLAGS="-m64 -I/usr/include/odbc -DHAVE_OPENSSL_BIO_METHOD $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)"
CONFIGURE_OPTIONS +=	CXXFLAGS="-m64 $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)"

COMPONENT_INSTALL_TARGETS += samples

# Build dependencies
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)
REQUIRED_PACKAGES += $(MYSQL_BASEPKG)
REQUIRED_PACKAGES += library/popt

# Auto-generated dependencies
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += codec/speex
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/freetds
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gmime
REQUIRED_PACKAGES += library/jansson
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/libical
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/neon
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/spandsp
REQUIRED_PACKAGES += library/speexdsp
REQUIRED_PACKAGES += library/unixodbc
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua-53
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libupnp
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += web/curl
