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
# Copyright 2022 Niklas Poslovski
#

USE_OPENSSL11= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		lighttpd
COMPONENT_VERSION=	1.4.70
COMPONENT_SUMMARY=	The Lighttpd Web Server
COMPONENT_PROJECT_URL=	https://www.lighttpd.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:bc96e5571d937279aa7cfdc9c9de95bcc457ab6feafff6264aa8832d026068bc
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	web/server/$(COMPONENT_NAME)-14
COMPONENT_CLASSIFICATION= Web Services/Application and Web Servers
COMPONENT_LICENSE=	Lighttpd license
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL= 0

ELFEDIT= /usr/bin/elfedit

LIGHTTPD_INSTALLDIR= /usr/lighttpd/1.4

CFLAGS += -I/usr/include/openldap
LDFLAGS += -lldap_r-2.4
LDFLAGS += -lnsl -lsocket

# libtool linking will fail unless we re-create configure.
COMPONENT_PREP_ACTION = ( cd $(@D) ; $(CONFIG_SHELL) autogen.sh )

# lighttpd is logging using __FILE__ macro. Cloning will make this happen
# using just source file names (without full absolute paths).
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_PREFIX= $(LIGHTTPD_INSTALLDIR)
CONFIGURE_MANDIR= $(CONFIGURE_PREFIX)/man
CONFIGURE_SBINDIR = $(CONFIGURE_PREFIX)/sbin
CONFIGURE_BINDIR = $(CONFIGURE_PREFIX)/bin

CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --without-lua
CONFIGURE_OPTIONS += --with-openssl=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS += --with-pcre
CONFIGURE_OPTIONS += --with-mysql=$(MYSQL_CONFIG)
CONFIGURE_OPTIONS += --with-ldap
CONFIGURE_OPTIONS += --enable-rpath
CONFIGURE_OPTIONS += LDFLAGS="-L$(OPENSSL_LIBDIR) -L$(MYSQL_LIBDIR)"
CONFIGURE_OPTIONS += LIBS="-L$(OPENSSL_LIBDIR) -L$(MYSQL_LIBDIR)"

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# mod_vhostdb_mysql.so doesn't find its mariadb lib without this:
COMPONENT_POST_INSTALL_ACTION += \
	$(ELFEDIT) -e "dyn:runpath $(MYSQL_LIBDIR)" \
                    $(PROTO_DIR)$(LIGHTTPD_INSTALLDIR)/lib/$(MACH64)/mod_vhostdb_mysql.so

# Auto-generated dependencies
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/fastcgi/spawn-fcgi
