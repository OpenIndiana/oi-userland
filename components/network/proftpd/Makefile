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
# Copyright (c) 2011, 2019, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		proftpd
COMPONENT_VERSION=	1.3.8
COMPONENT_SUBVERSION=	c
HUMAN_VERSION=		$(COMPONENT_VERSION)$(COMPONENT_SUBVERSION)
COMPONENT_PROJECT_URL=	http://www.proftpd.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:2a48f2ca338456e750d2373bf671025ed799e04e0baa16c7bb8dbfd67d8734d2
COMPONENT_ARCHIVE_URL=	ftp://ftp.proftpd.org/distrib/source/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

# mod_gss subcomponent
COMPONENT_NAME_1=	mod_gss
COMPONENT_VERSION_1=	1.3.9
COMPONENT_SRC_1=	$(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:de8babe0f13800da2142be74d82686af3984419a2ec09c86516467be58bce9a7
COMPONENT_ARCHIVE_URL_1= http://downloads.sourceforge.net/gssmod/$(COMPONENT_ARCHIVE_1)

TEST_TARGET=$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_BINDIR.64 =   $(USRLIBDIR)/proftpd/bin
CONFIGURE_SBINDIR.64 =  $(USRLIBDIR)/proftpd/sbin

LDFLAGS +=	$(CC_BITS)

# Do not use openssl 1.1.1
CFLAGS  += -I$(OPENSSL_INCDIR)
LDFLAGS += -L$(OPENSSL_LIBDIR)

# Remove -D_POSIX_PTHREAD_SEMANTICS and this comment after move to S12_45.
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS) -I/usr/include/kerberosv5 -DHAVE_KRB5_H=1 -DKRB5_DLLIMP= -DHAVE__GETGRPSBYMEMBER -D_POSIX_PTHREAD_SEMANTICS"
# Force immediate binding because of chroot().
CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS) -z guidance=nolazyload -z nolazyload -lbsm"
CONFIGURE_OPTIONS +=	install_user=`id -nu`
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
CONFIGURE_OPTIONS +=	--with-modules=mod_solaris_priv
CONFIGURE_OPTIONS +=	--with-shared=mod_facl:mod_wrap:mod_tls:mod_auth_gss:mod_gss:mod_ifsession
CONFIGURE_OPTIONS +=	--enable-buffer-size=16384
CONFIGURE_OPTIONS +=	--disable-ncurses

# Copy Solaris modules and GSSAPI modules to proftpd source tree
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CP) mod_solaris_audit.c $(SOURCE_DIR)/contrib && \
	$(CP) mod_solaris_priv.c $(SOURCE_DIR)/contrib && \
	cd $(BUILD_DIR) && \
	/usr/gnu/bin/tar xzf $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1) && \
	cd $(COMPONENT_SRC_1) && \
	$(GPATCH) < ../../mod_gss-patches/002.27914767.patch ; \
	$(CP) $(COMPONENT_DIR)/krb5-config $(BUILD_DIR) && \
	chmod u+x $(BUILD_DIR)/krb5-config && \
	./configure CC="$(CC)" CFLAGS="$(CC_BITS) -I/usr/include/kerberosv5"  --with-krb5-config=$(BUILD_DIR)/krb5-config && \
	$(CP) mod_gss.c mod_auth_gss.c $(SOURCE_DIR)/contrib && \
	$(CP) mod_gss.h $(SOURCE_DIR)/include && \
	$(CP) mod_gss.html $(SOURCE_DIR)/doc/contrib && \
	$(CLONEY) $(SOURCE_DIR) $(@D))

# proftpd configure and build is not ready for run out of the source tree
CONFIGURE_SCRIPT =	$(@D)/configure

# Do not apply the standard license transforms for this component. The
# license actions in the proftpd.p5m file are already tagged with the
# attributes.
LICENSE_TRANSFORMS =

# libcheck and specific Perl Test::Unit version is required for full test

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
