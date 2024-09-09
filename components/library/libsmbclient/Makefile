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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
# Copyright 2023,2024 Friedrich Kink. All rights reserved.
#

BUILD_BITS = 64
BUILD_STYLE = waf
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		samba
COMPONENT_VERSION=	4.21.0
COMPONENT_SUMMARY=	A library that permits GPLv2 applications to manipulate CIFS/SMB network resources
COMPONENT_PROJECT_URL=	https://www.samba.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:09bb56db4ce003cafdbebe9bad368c4f4ff1945f732d18077d52f36ab20cef88
COMPONENT_ARCHIVE_URL=	https://download.samba.org/pub/samba/stable/$(COMPONENT_ARCHIVE)
#COMPONENT_SIG_URL =     https://download.samba.org/pub/samba/stable/$(COMPONENT_SRC).tar.asc
COMPONENT_FMRI=		library/samba/libsmbclient
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# waf
WAF = PYTHONHASHSEED=1 $(PYTHON) $(SOURCE_DIR)/buildtools/bin/waf

# Compiler settings
CFLAGS	+=	-std=c17 -D_POSIX_PTHREAD_SEMANTICS -DHAVE_AUXV_T -DHCRYPTO_DEF_PROVIDER=hcrypto

LDFLAGS +=	-R/usr/lib/libsmbclient
LDFLAGS +=	-R/usr/lib/libsmbclient/private

LDFLAGS +=      -lrt -lsec -lcrypt -lmd5 -lsocket -lnsl -lsendfile
LDFLAGS +=      -lldap-2.6 -lsendfile -lavahi-common -lavahi-core

CPPFLAGS +=	$(CPP_LARGEFILES) $(CPP_XPG6MODE)
CPPFLAGS +=	-I/usr/include/openldap -I/usr/include/jansson

# Flag is not picked up for lib/replace
LDFLAGS +=     $(LD_SSP)

LD_OPTIONS += 	-B direct

# to avoid a clash with system gssapi.h (some declaration are not compatible)
COMPONENT_POST_CONFIGURE_ACTION= ( \
        $(RM) $(@D)/third_party/heimdal/lib/gssapi/gssapi.h; \
         );

CONFIGURE_PREFIX =      /usr/lib/libsmbclient

# !!! Note, this is not a configure.mk-based Makefile !!!
# --enable-fhs should not be on
CONFIGURE_OPTIONS +=	--prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=	--exec-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=	--bindir=$(CONFIGURE_PREFIX)/bin
CONFIGURE_OPTIONS +=	--sbindir=$(CONFIGURE_PREFIX)/sbin
CONFIGURE_OPTIONS +=	--libdir=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=	--with-privatelibdir=$(CONFIGURE_PREFIX)/private
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)/samba
CONFIGURE_OPTIONS +=	--with-pammodulesdir=$(CONFIGURE_PREFIX)/security
CONFIGURE_OPTIONS +=	--datarootdir=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=	--mandir=$(USRSHAREMANDIR)
CONFIGURE_OPTIONS +=	--htmldir=/usr/share/samba/swat/help
CONFIGURE_OPTIONS +=	--includedir=$(USRINCDIR)/libsmbclient
CONFIGURE_OPTIONS +=	--with-privatedir=$(ETCDIR)/samba/private
CONFIGURE_OPTIONS +=	--localstatedir=$(VARDIR)/samba
CONFIGURE_OPTIONS +=	--with-logfilebase=$(VARDIR)/samba/log
CONFIGURE_OPTIONS +=	--sharedstatedir=$(VARDIR)/samba/com
CONFIGURE_OPTIONS +=	--libexecdir=$(CONFIGURE_PREFIX)/libexec
CONFIGURE_OPTIONS +=	--with-bind-dns-dir=$(CONFIGURE_PREFIX)/bind-dns

CONFIGURE_OPTIONS +=	--with-static-modules=
CONFIGURE_OPTIONS +=	--with-shared-modules=
CONFIGURE_OPTIONS +=	--with-ads
CONFIGURE_OPTIONS +=	--with-winbind
CONFIGURE_OPTIONS +=	--with-ldap
CONFIGURE_OPTIONS +=	--nopyo
CONFIGURE_OPTIONS +=	--disable-rpath
CONFIGURE_OPTIONS +=	--disable-rpath-private-install 
CONFIGURE_OPTIONS +=	--bundled-libraries=ALL
CONFIGURE_OPTIONS +=	--disable-python
CONFIGURE_OPTIONS +=	--without-ad-dc
CONFIGURE_OPTIONS +=    --disable-spotlight

CONFIGURE_ENV +=        CPP="$(CC) -E"
CONFIGURE_ENV +=        CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV +=        CUPS_CONFIG=$(USRBINDIR)/cups-config
CONFIGURE_ENV +=        PATH=$(GNUBIN.$(BITS)):$(USRBINDIR.$(BITS)):$(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += library/file-monitor/gamin
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/jansson
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/network/avahi
