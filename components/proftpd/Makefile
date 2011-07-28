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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		proftpd
COMPONENT_VERSION=	1.3.3
COMPONENT_SUBVERSION=	e
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)$(COMPONENT_SUBVERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:823e94c24447936ade6ae3948fe638077e0ba933
COMPONENT_ARCHIVE_URL=	ftp://ftp.proftpd.org/distrib/source/$(COMPONENT_ARCHIVE)

# mod_gss subcomponent
COMPONENT_NAME_1=	mod_gss
COMPONENT_VERSION_1=	$(COMPONENT_VERSION)
COMPONENT_SRC_1=	$(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= sha1:b17015a49e41ee643f1891940f9f3f8a7d77e522
COMPONENT_ARCHIVE_URL_1= http://downloads.sourceforge.net/gssmod/$(COMPONENT_ARCHIVE_1)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# IPS_COMPONENT_VERSION is by default set to $(COMPONENT_VERSION) but it is not
# enough for us. We need to include the $(COMPONENT_SUBVERSION) somehow.
# Because the IPS_COMPONENT_VERSION cannot contain letters we used '.0.5'
# instead of 'e'.
IPS_COMPONENT_VERSION=  $(COMPONENT_VERSION).0.5

CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS) -I/usr/include/kerberosv5 -DHAVE_KRB5_H=1 -DKRB5_DLLIMP="
CONFIGURE_OPTIONS +=	LDFLAGS="-lbsm"
CONFIGURE_OPTIONS +=	install_user=$(LOGNAME)
CONFIGURE_OPTIONS +=	install_group=`groups | cut -f 1 -d ' '`
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	--localstatedir=/var/run
CONFIGURE_OPTIONS +=	--libexecdir=$(USRLIBDIR)/proftpd
CONFIGURE_OPTIONS +=	--enable-ipv6
CONFIGURE_OPTIONS +=	--enable-ctrls
CONFIGURE_OPTIONS +=	--enable-facl
CONFIGURE_OPTIONS +=	--enable-nls
CONFIGURE_OPTIONS +=	--enable-dso
CONFIGURE_OPTIONS +=	--enable-openssl
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--with-modules=mod_solaris_audit:mod_solaris_priv
CONFIGURE_OPTIONS +=	--with-shared=mod_facl:mod_wrap:mod_tls:mod_auth_gss:mod_gss
CONFIGURE_OPTIONS +=	--enable-buffer-size=16384

# Copy Solaris modules and GSSAPI modules to proftpd source tree
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CP) mod_solaris_audit.c $(SOURCE_DIR)/contrib ; \
	$(CP) mod_solaris_priv.c $(SOURCE_DIR)/contrib ; \
	cd $(BUILD_DIR) ; \
	$(UNPACK) $(UNPACK_ARGS) ../$(COMPONENT_ARCHIVE_1) ; \
	cd $(COMPONENT_SRC_1) ; \
	./configure CC="$(CC)" CFLAGS="-I/usr/include/kerberosv5" ; \
	$(CP) mod_gss.c mod_auth_gss.c $(SOURCE_DIR)/contrib ; \
	$(CP) mod_gss.h $(SOURCE_DIR)/include ; \
	$(CP) mod_gss.html $(SOURCE_DIR)/doc/contrib ; \
	$(CLONEY) $(SOURCE_DIR) $(@D))

# proftpd configure and build is not ready for run out of the source tree
CONFIGURE_SCRIPT =	$(@D)/configure

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)
# libcheck and specific Perl Test::Unit version is required for full test

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
