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
# Copyright (c) 2010, Oracle and/or it's affiliates.  All rights reserved.
#
include ../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin

COMPONENT_NAME=		bind
COMPONENT_VERSION=	9.7.0-P2
IPS_PKG_NAME =		network/dns/bind
COMPONENT_CLASSIFICATION="Applications/Internet utility"
COMPONENT_DESCRIPTION=	"Berkeley Internet Name Domain server and utilities"
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL =	http://www.isc.org/software/bind
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:4b805d4a66075a88c93c5b852b928da96467aa2d
COMPONENT_ARCHIVE_URL=	http://ftp.isc.org/isc/bind9/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS +=	--with-libtool
CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--localstatedir=/var
CONFIGURE_OPTIONS +=	--with-openssl
CONFIGURE_OPTIONS +=	--enable-threads=yes
CONFIGURE_OPTIONS +=	--enable-devpoll=yes
CONFIGURE_OPTIONS +=	--disable-openssl-version-check
CONFIGURE_OPTIONS +=	--enable-fixed-rrset
CONFIGURE_OPTIONS +=	--disable-getifaddrs

# because IPS doesn't deal with -P2 in the version string
IPS_COMPONENT_VERSION=	9.7.0

PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/archive-libraries-drop
PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/libtool-drop
PKGMOGRIFY_TRANSFORMS +=	manifest-drop

PKG_HARDLINKS +=	usr/sbin/named
PKG_HARDLINKS +=	usr/share/man/man3/lwres_addr_parse.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_buffer.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_conf_clear.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_context.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_endhostent.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_freeaddrinfo.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_freehostent.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_gabn.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_gnba.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_herror.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_inetntop.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_lwpacket_parseheader.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_noop.3

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)
