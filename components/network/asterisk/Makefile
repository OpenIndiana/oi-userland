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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		asterisk
COMPONENT_VERSION=	15.1.4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:8ce3ffbff473410ae0ed0472adea22b01a20f9ec784ebfec51393282028acc16
COMPONENT_PROJECT_URL=	http://www.asterisk.org
COMPONENT_ARCHIVE_URL=	http://downloads.asterisk.org/pub/telephony/asterisk/old-releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D));

CFLAGS += -I/usr/include/jansson

LDFLAGS+= -L$(PG_LIBDIR.$(BITS)) -R$(PG_LIBDIR.$(BITS))

# asterisk uses a bit of dlsym() magic to overwrite some libssl
# functions. The magic is defeated by -Bdirect -zignore
LD_B_DIRECT=
LD_Z_IGNORE=

PATCH_LEVEL = 0

CONFIGURE_BINDIR=	/usr/bin
CONFIGURE_SBINDIR=	/usr/sbin

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--localstatedir=/var
CONFIGURE_OPTIONS +=	--without-oss
CONFIGURE_OPTIONS +=	--with-pjproject-bundled=no
CONFIGURE_OPTIONS +=	--with-gsm=internal
CONFIGURE_OPTIONS +=	PG_CONFIG=$(PG_BINDIR)/pg_config

COMPONENT_INSTALL_TARGETS += samples

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += database/postgres-94/developer

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += codec/speex
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += database/postgres-94/library
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/freetds
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gmime
REQUIRED_PACKAGES += library/gnu-libiconv
REQUIRED_PACKAGES += library/jansson
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/libical
REQUIRED_PACKAGES += library/libidn2
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += library/libproxy
REQUIRED_PACKAGES += library/libssh2
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/neon
REQUIRED_PACKAGES += library/nghttp2
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/speexdsp
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/gcc-6-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += web/curl
