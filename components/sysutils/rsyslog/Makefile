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
# Copyright (c) 2012, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2022 Niklas Poslovski
# Copyright (c) 2022 Friedrch Kink
#

USE_OPENSSL11=	yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rsyslog
COMPONENT_VERSION=	8.2302.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://www.rsyslog.com/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:25415f85b662615ce3c83077d53758029e8743cb5929044bfd3564e3d626a3b9
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)files/download/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_SUMMARY=	reliable and extended syslogd
COMPONENT_FMRI=		system/rsyslog
COMPONENT_LICENSE=	GPLv3
COMPONENT_CLASSIFICATION= System/Administration and Configuration

include $(WS_TOP)/make-rules/common.mk

# to make REQUIRED_PACKAGES happy when evaluating ompgsql.so
LDFLAGS += -Wl,-R'/usr/postgres/14/lib/amd64'

COMPONENT_PREP_ACTION =        ( cd $(@D) && autoreconf -f -i )

CONFIGURE_OPTIONS +=    --enable-imsolaris
CONFIGURE_OPTIONS +=    --enable-impstats
CONFIGURE_OPTIONS +=    --enable-imfile
CONFIGURE_OPTIONS +=    --enable-improg
CONFIGURE_OPTIONS +=    --enable-imptcp
CONFIGURE_OPTIONS +=    --enable-mail
CONFIGURE_OPTIONS +=    --enable-gssapi_krb5
CONFIGURE_OPTIONS +=    --enable-gnutls
CONFIGURE_OPTIONS +=    --enable-openssl
CONFIGURE_OPTIONS +=    --enable-usertools
CONFIGURE_OPTIONS +=    --enable-mysql
CONFIGURE_OPTIONS +=    --enable-pgsql
CONFIGURE_OPTIONS +=    --enable-snmp
CONFIGURE_OPTIONS +=    --enable-libzstd
CONFIGURE_OPTIONS +=    --enable-omhttp
CONFIGURE_OPTIONS +=	--enable-omruleset
CONFIGURE_OPTIONS +=	--enable-omuxsock
CONFIGURE_OPTIONS +=	--enable-omfile-hardened
CONFIGURE_OPTIONS +=	--enable-omprog
#CONFIGURE_OPTIONS +=	--enable-ommongodb
CONFIGURE_OPTIONS +=	--enable-omtcl
CONFIGURE_OPTIONS +=	--enable-omhttpfs
CONFIGURE_OPTIONS +=	--enable-mmsnmptrapd
CONFIGURE_OPTIONS +=	--enable-mmjsonparse
CONFIGURE_OPTIONS +=	--enable-mmanon
CONFIGURE_OPTIONS +=	--enable-mmutf8fix
CONFIGURE_OPTIONS +=	--enable-mmcount
CONFIGURE_OPTIONS +=	--enable-mmtaghostname
CONFIGURE_OPTIONS +=    --enable-pmlastmsg
CONFIGURE_OPTIONS +=    --disable-klog
CONFIGURE_OPTIONS +=    --sbindir=$(USRLIBDIR)/rsyslog

CONFIGURE_ENV += LD_OPTIONS="$(LD_OPTIONS)"

PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files

# manually added
REQUIRED_PACKAGES += library/libevent2

# Auto-generated dependencies
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libestr
REQUIRED_PACKAGES += library/libfastjson
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += web/curl
