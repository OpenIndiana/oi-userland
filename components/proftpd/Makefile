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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		proftpd
COMPONENT_VERSION=	1.3.5
COMPONENT_SUBVERSION=	b
HUMAN_VERSION=		$(COMPONENT_VERSION)$(COMPONENT_SUBVERSION)
COMPONENT_PROJECT_URL=	http://www.proftpd.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:afc1789f2478acf88dfdc7d70da90a4fa2786d628218e9574273295d044b4fc8
COMPONENT_ARCHIVE_URL=	ftp://ftp.proftpd.org/distrib/source/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	service/proftpd
TPNO_PROFTPD=		27604
COMPONENT_ANITYA_ID=	7609

# mod_gss subcomponent
COMPONENT_NAME_1=	mod_gss
COMPONENT_VERSION_1=	1.3.6
COMPONENT_SRC_1=	$(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:bd1cb3f8ba0668981beb54d8b4de10ab204199327a464debd9da19196bbb23c4
COMPONENT_ARCHIVE_URL_1= http://downloads.sourceforge.net/gssmod/$(COMPONENT_ARCHIVE_1)
TPNO_MOD_GSS=		13480

# Requires 64-bit version of libwrap from ON, available in S12 but not 11.3,
# so do not publish.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

# Enable adiheap and adistack security extensions
ADIHEAP_MODE =	$(ADIHEAP_ENABLE)
ADISTACK_MODE =	$(ADISTACK_ENABLE)

# libcheck and specific Perl Test::Unit version is required for full test
TEST_TARGET= $(SKIP_TEST)
include $(WS_MAKE_RULES)/common.mk

# IPS_COMPONENT_VERSION is by default set to $(COMPONENT_VERSION) but it is not
# enough for us. We need to include the $(COMPONENT_SUBVERSION) somehow.
# Because the IPS_COMPONENT_VERSION cannot contain letters
# ...we will use '.2' instead of 'b'.
IPS_COMPONENT_VERSION=  $(COMPONENT_VERSION).2

CFLAGS += -I$(USRINCDIR)/kerberosv5 -DHAVE_KRB5_H=1 -DKRB5_DLLIMP= -DHAVE__GETGRPSBYMEMBER -D_SOLARIS_DTRACE
ifeq ($(OS_VERSION), 5.11)
CFLAGS += -D_POSIX_PTHREAD_SEMANTICS
endif
LDFLAGS +=	-m$(BITS)
# Force immediate (no-lazy) binding because of chroot() can loose the access into (/usr)/lib
LDFLAGS +=	-z guidance=nolazyload -z nolazyload -lbsm

CONFIGURE_OPTIONS +=	install_user=`id -nu`
CONFIGURE_OPTIONS +=	install_group=`groups | cut -f 1 -d ' '`
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	--localstatedir=$(VARDIR)/run
CONFIGURE_OPTIONS +=	--libexecdir=$(USRLIBDIR)/proftpd/$(MACH64)
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

# Copy Solaris modules and GSSAPI modules to proftpd source tree.
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

# Build Solaris dtrace object files and copy to proftpd build tree.
COMPONENT_PRE_BUILD_ACTION = \
	(cd dtrace && make CP="$(CP)" CC="$(CC)" BD="$(BUILD_DIR)/$(MACH$(BITS))" BITS="$(BITS)")

# proftpd configure and build is not ready for run out of the source tree
CONFIGURE_SCRIPT =	$(@D)/configure

# Do not apply the standard license transforms for this component. The
# license actions in the proftpd.p5m file are already tagged with the
# attributes.
LICENSE_TRANSFORMS =

REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += security/kerberos-5
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/network
