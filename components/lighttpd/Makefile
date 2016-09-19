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

COMPONENT_NAME=		lighttpd
COMPONENT_VERSION=	1.4.41
COMPONENT_PROJECT_URL=	http://www.lighttpd.net/
COMPONENT_ARCHIVE_HASH=	\
    sha256:8a5749e218237fafc3119dd8a4fcf510ea728728b3fcf1193fcad7209be4b6d7
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)

TPNO=			31753

LIGHTTPD_INSTALLDIR=$(USRDIR)/lighttpd/1.4

include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL=0

# lighttpd is logging using __FILE__ macro. Cloning will make this happen
# using just source file names (without full absolute paths).
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_PREFIX= $(LIGHTTPD_INSTALLDIR)
CONFIGURE_MANDIR= $(CONFIGURE_PREFIX)/man

# Force lighttpd binaries and private modules to standard path
CONFIGURE_LIBDIR.64 = $(CONFIGURE_PREFIX)/lib

CFLAGS += "-I/usr/include/openldap"
LDFLAGS += "-lldap_r-2.4"

CONFIGURE_OPTIONS +=	--with-pic
CONFIGURE_OPTIONS +=	--with-lua
CONFIGURE_OPTIONS +=	--with-openssl
CONFIGURE_OPTIONS +=	--with-pcre
CONFIGURE_OPTIONS +=	--with-ldap
CONFIGURE_OPTIONS +=	--with-mysql=$(USRDIR)/mysql/5.7/bin/mysql_config
CONFIGURE_OPTIONS +=    PCRECONFIG="$(USRBINDIR64)/pcre-config"

COMPONENT_TEST_TRANSFORMS += \
	'-e "s/, *[0-9][0-9]* wallclock secs (.*CPU)$$/, <TIMINGS REMOVED>/" ' \
	'-e "/^preparing infrastructure/,/make\[4\]: Leaving directory/p" ' \
	'-e "/.*/d" '

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += database/mysql-57
REQUIRED_PACKAGES += database/mysql-57/library
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/security/openssl/openssl-fips-140
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/network
REQUIRED_PACKAGES += system/network/ldap/openldap
REQUIRED_PACKAGES += web/fastcgi/spawn-fcgi
