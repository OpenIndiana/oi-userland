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

COMPONENT_NAME=		wireshark
COMPONENT_VERSION=	2.2.1
COMPONENT_PROJECT_URL=	http://www.wireshark.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:900e22af04c8b35e0d02a25a360ab1fb7cfe5ac18fc48a9afd75a7103e569149
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/src/all-versions/$(COMPONENT_ARCHIVE)

TPNO=			32120

# Enable adiheap and adistack security extensions
ADIHEAP_MODE =	$(ADIHEAP_ENABLE)
ADISTACK_MODE =	$(ADISTACK_ENABLE)

TEST_TARGET= $(NO_TESTS)

# Depends on newer cairo, which cannot be updated in S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/common.mk

# Micro version for easy libraries packaging
MICRO_VERSION:= $(shell echo $(COMPONENT_VERSION) | awk -F. '{ print $$3 }')
PKG_MACROS+= MICRO_VERSION=$(MICRO_VERSION)

PATCH_LEVEL=0

# Look for gnutls-3 pkg-config & libraries before the defaults
PKG_CONFIG_PATH.64 := $(PKG_CONFIG_PATH.64)/gnutls-3:$(PKG_CONFIG_PATH.64)
LDFLAGS += -L$(USRLIBDIR64)/gnutls-3

# Reported via bug 12923
CFLAGS += -I/usr/include/kerberosv5

CONFIGURE_BINDIR.64= $(CONFIGURE_SBINDIR.64)

CONFIGURE_OPTIONS +=	--disable-usr-local
CONFIGURE_OPTIONS +=	--disable-androiddump
CONFIGURE_OPTIONS +=	--disable-randpkt
CONFIGURE_OPTIONS +=	--disable-dftest
CONFIGURE_OPTIONS +=	--with-krb5
CONFIGURE_OPTIONS +=	--with-qt=no
CONFIGURE_OPTIONS +=	--with-gtk=3
CONFIGURE_OPTIONS +=	\
  PATH="$(USRDIR)/perl5/bin:$(GNUBIN)/$(MACH64):$(GNUBIN):$(USRBIN.64):$(PATH)"

# We need to avoid RPATH=/usr/lib in Wireshark libraries so that we can
# create successfully IPS package of different Wireshark branch than is
# installed on build system without dependency errors.
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D); \
	sed -e 's,-R/usr/lib/$(MACH64),,' \
	    -e 's,-R/usr/lib,,' \
	    -e 's,-R\$$libdir,,' \
		config.status > config.status.new; \
	mv config.status.new config.status; \
	chmod 755 config.status; \
	./config.status)

# During install libtool will relink libwireshark library so that it
# requires libwiretap version from system and not from proto area.
# This workaround is only needed when CBE contains older libwiretap.
LIBWIRESHARK=$(PROTOUSRLIBDIR64)/libwireshark.so.8.0.$(MICRO_VERSION)
COMPONENT_POST_INSTALL_ACTION = \
	(WTAP=`$(ELFEDIT) -e dyn:dump $(LIBWIRESHARK) | grep 'libwiretap' | awk '{print $$4}'` \
	; $(ELFEDIT) -e "dyn:value -s -with-valstr $$WTAP libwiretap.so.6" $(LIBWIRESHARK) )

REQUIRED_PACKAGES += developer/lexer/flex
REQUIRED_PACKAGES += developer/parser/bison
REQUIRED_PACKAGES += diagnostic/wireshark/wireshark-common
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += security/kerberos-5
REQUIRED_PACKAGES += system/library/libpcap
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
