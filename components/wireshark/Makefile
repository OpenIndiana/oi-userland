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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		wireshark
COMPONENT_VERSION=	1.12.4
COMPONENT_PROJECT_URL=	http://www.wireshark.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:de804e98e252e4b795d28d6ac2d48d7f5aacd9b046ee44d44266983795ebc312
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/src/all-versions/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/wireshark

TPNO=			21830

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Micro version for easy libraries packaging
MICRO_VERSION:= $(shell echo $(COMPONENT_VERSION) | awk -F. '{ print $$3 }')
PKG_MACROS+= MICRO_VERSION=$(MICRO_VERSION)

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

PATCH_LEVEL=0

# We don't have automake 1.14 yet. Thus need to reconfigure with older one.
COMPONENT_PREP_ACTION += ( cd $(@D) ; $(CONFIG_SHELL) autogen.sh );

CONFIGURE_OPTIONS +=	--bindir=/usr/sbin
CONFIGURE_OPTIONS +=	--disable-usr-local
CONFIGURE_OPTIONS +=	--disable-randpkt
CONFIGURE_OPTIONS +=	--disable-dftest
CONFIGURE_OPTIONS +=	--with-krb5
CONFIGURE_OPTIONS +=	--with-qt=no
CONFIGURE_OPTIONS +=	--with-gtk2=yes
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)" 
CONFIGURE_OPTIONS +=	PATH="/usr/perl5/bin:/usr/gnu/bin:$(PATH)"

# Use the 64-bit versions of pkg-config files
CONFIGURE_ENV +=	PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"

# Workaround for Bug 19143303
studio_OPT =	-xO3

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
# This shall be removed once CBE is updated to contain Wireshark 1.12
# (see Bug 20627618).
COMPONENT_POST_INSTALL_ACTION = \
	(/usr/bin/elfdump -d $(PROTO_DIR)/usr/lib/$(MACH64)/libwireshark.so.5.0.4 | \
	    grep 'libwiretap.so.3' && /usr/bin/elfedit \
	    -e 'dyn:value -s -with-valstr libwiretap.so.3 libwiretap.so.4' \
	    $(PROTO_DIR)/usr/lib/$(MACH64)/libwireshark.so.5.0.4; true)

configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += developer/lexer/flex
REQUIRED_PACKAGES += developer/parser/bison
REQUIRED_PACKAGES += diagnostic/wireshark/wireshark-common
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnutls
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libpcap
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
