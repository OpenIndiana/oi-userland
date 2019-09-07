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
# Copyright (c) 2011, 2014, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2020, Michal Nowak
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		wireshark
COMPONENT_VERSION=	2.2.17
COMPONENT_PROJECT_URL=	http://www.wireshark.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:923d39ff9c6df83b9594868542061da33bf330e12526778a8cb3adcf912eebb0
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/src/all-versions/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET:		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# Micro version for easy libraries packaging
MICRO_VERSION:= $(shell echo $(COMPONENT_VERSION) | awk -F. '{ print $$3 }')
PKG_MACROS+= MICRO_VERSION=$(MICRO_VERSION)

PATCH_LEVEL=0

# We don't have automake 1.14 yet. Thus need to reconfigure with older one.
COMPONENT_PREP_ACTION += ( cd $(@D) ; $(CONFIG_SHELL) autogen.sh );

CONFIGURE_OPTIONS +=	--bindir=/usr/sbin
CONFIGURE_OPTIONS +=	--disable-androiddump
CONFIGURE_OPTIONS +=	--disable-randpkt
CONFIGURE_OPTIONS +=	--disable-dftest
CONFIGURE_OPTIONS +=	--with-krb5
CONFIGURE_OPTIONS +=	--with-qt=no
CONFIGURE_OPTIONS +=	--with-gtk=yes
CONFIGURE_OPTIONS +=	PATH="/usr/perl5/bin:/usr/gnu/bin:$(PATH)"

LDFLAGS += -lsocket -lnsl
LD_B_DIRECT=

# We need to avoid RPATH=/usr/lib in Wireshark libraries so that we can
# create successfully IPS package of different Wireshark branch than is
# installed on build system without dependency errors.
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D); \
	sed -e 's,-L/usr/lib -R/usr/lib,,' -e 's,-R/usr/lib,,' \
		config.status > config.status.new; \
	mv config.status.new config.status; \
	chmod 755 config.status; \
	./config.status)

# Auto-generated dependencies
REQUIRED_PACKAGES += database/geoip
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libpcap
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libgcrypt
